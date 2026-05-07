#include "sdodps_master.hpp"
#include "sdodps_slave_mcu.hpp"
#include "sdodps_slave_pcu.hpp"

#include <cstdint>
#include <cstdio>

#define CHECK(expr) \
	do { \
		if (!(expr)) { \
			std::fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #expr); \
			return 1; \
		} \
	} while (0)

struct Link {
	sdodps::Master master;
	std::uint32_t pcu_dbc_hash = 0x12345678u;
	std::uint8_t send_asms = 0u;
	float kp_batt = 0.0f;
	std::uint16_t hook_var = 0u;
	unsigned hook_count = 0u;
};

static Link *g_link = nullptr;

static bool master_tx(std::uint32_t id, std::uint8_t dlc, std::uint64_t payload)
{
	(void)dlc;
	return sdodps::SlavePcu::process(id, payload) || sdodps::SlaveMcu::process(id, payload);
}

static bool slave_tx(std::uint32_t id, std::uint8_t dlc, std::uint64_t payload)
{
	(void)dlc;
	return g_link->master.process(id, payload);
}

static bool read_pcu_dbc_hash(std::uint32_t *out)
{
	*out = g_link->pcu_dbc_hash;
	return true;
}

static bool read_send_asms(std::uint8_t *out)
{
	*out = g_link->send_asms;
	return true;
}

static bool write_send_asms(std::uint8_t value)
{
	g_link->send_asms = value;
	return true;
}

static bool read_kp_batt(float *out)
{
	*out = g_link->kp_batt;
	return true;
}

static bool write_kp_batt(float value)
{
	g_link->kp_batt = value;
	return true;
}

static void value_hook(std::uint32_t id, std::uint16_t var_id)
{
	(void)id;
	g_link->hook_var = var_id;
	g_link->hook_count++;
}

static std::uint64_t mask_bits(unsigned bit_length)
{
	return bit_length >= 64u ? 0xffffffffffffffffULL : ((1ULL << bit_length) - 1ULL);
}

static void set_bits(std::uint64_t *payload, unsigned start, unsigned bit_length, std::uint64_t value)
{
	const std::uint64_t mask = mask_bits(bit_length);
	*payload = (*payload & ~(mask << start)) | ((value & mask) << start);
}

static sdodps::Frame make_frame(std::uint32_t id, sdodps::Opcode opcode, std::uint16_t var_id, std::uint8_t flags, std::uint64_t value, unsigned bit_length)
{
	sdodps::Frame frame { id, 7u, 0u };
	set_bits(&frame.payload, 0u, 8u, static_cast<std::uint8_t>(opcode));
	set_bits(&frame.payload, 8u, 10u, var_id);
	set_bits(&frame.payload, 18u, 6u, flags);
	set_bits(&frame.payload, 24u, bit_length, value);
	return frame;
}

int main()
{
	Link link;
	g_link = &link;
	link.master.set_tx_callback(master_tx);
	link.master.set_value_hook(value_hook);
	sdodps::SlavePcu::set_tx_callback(slave_tx);
	sdodps::SlaveMcu::set_tx_callback(slave_tx);

	sdodps::SlavePcu::set_dbc_hash_reader(read_pcu_dbc_hash);

	link.master.set_expected_pcu_hash(link.pcu_dbc_hash + 1u);
	CHECK(!link.master.pcu_hash_verified());
	CHECK(!link.master.request_pcu(sdodps::PcuVar::Kp_batt));
	CHECK(link.master.request_pcu(sdodps::PcuVar::dbc_hash));
	CHECK(link.master.has_pcu_value(sdodps::PcuVar::dbc_hash));
	CHECK(link.hook_count == 1u);
	CHECK(link.hook_var == static_cast<std::uint16_t>(sdodps::PcuVar::dbc_hash));

	std::uint32_t dbc_hash = 0u;
	CHECK(link.master.take_pcu_dbc_hash(&dbc_hash));
	CHECK(dbc_hash == link.pcu_dbc_hash);
	CHECK(!link.master.pcu_hash_verified());
	CHECK(!link.master.request_pcu(sdodps::PcuVar::Kp_batt));

	link.master.set_expected_pcu_hash(link.pcu_dbc_hash);
	CHECK(!link.master.pcu_hash_verified());
	CHECK(!link.master.request_pcu(sdodps::PcuVar::Kp_batt));
	CHECK(link.master.request_pcu(sdodps::PcuVar::dbc_hash));
	CHECK(link.master.has_pcu_value(sdodps::PcuVar::dbc_hash));
	CHECK(link.hook_count == 2u);
	CHECK(link.hook_var == static_cast<std::uint16_t>(sdodps::PcuVar::dbc_hash));
	CHECK(link.master.take_pcu_dbc_hash(&dbc_hash));
	CHECK(dbc_hash == link.pcu_dbc_hash);
	CHECK(link.master.pcu_hash_verified());
	CHECK(!link.master.has_pcu_value(sdodps::PcuVar::dbc_hash));

	CHECK(sdodps::SlavePcu::write_send_asms(1u) == sdodps::Status::read_only);
	CHECK(!link.master.set_pcu_send_asms(1u));

	sdodps::SlavePcu::set_send_asms_reader(read_send_asms);
	sdodps::SlavePcu::set_send_asms_writer(write_send_asms);
	CHECK(link.master.set_pcu_send_asms(1u));
	CHECK(link.send_asms == 1u);
	std::uint8_t send_asms = 0u;
	CHECK(link.master.take_pcu_send_asms(&send_asms));
	CHECK(send_asms == 1u);

	sdodps::SlavePcu::set_Kp_batt_reader(read_kp_batt);
	sdodps::SlavePcu::set_Kp_batt_writer(write_kp_batt);
	CHECK(link.master.set_pcu_Kp_batt(12.5f));
	CHECK(link.kp_batt == 12.5f);
	float kp_batt = 0.0f;
	CHECK(link.master.take_pcu_Kp_batt(&kp_batt));
	CHECK(kp_batt == 12.5f);

	link.kp_batt = 4.25f;
	CHECK(link.master.request_pcu(sdodps::PcuVar::Kp_batt));
	CHECK(link.master.has_pcu_value(sdodps::PcuVar::Kp_batt));
	CHECK(link.master.take_pcu_Kp_batt(&kp_batt));
	CHECK(kp_batt == 4.25f);

	const sdodps::Frame req = make_frame(
		sdodps::SDO_Pcu_CAN_ID,
		sdodps::Opcode::GET_REQ,
		static_cast<std::uint16_t>(sdodps::PcuVar::send_asms),
		0u,
		0u,
		sdodps::Master::pcu_bit_length(sdodps::PcuVar::send_asms));
	CHECK(sdodps::SlavePcu::process(req.id, req.payload));
	CHECK(link.master.take_pcu_send_asms(&send_asms));
	CHECK(send_asms == 1u);

	std::puts("SDO_DPS generated C++ tests passed");
	return 0;
}
