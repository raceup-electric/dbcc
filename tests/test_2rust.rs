#![allow(dead_code)]

#[path = "../out/test_rust/bitfield_edge.rs"]
mod bitfield_edge;
#[path = "../out/test_rust/codec_matrix.rs"]
mod codec_matrix;
#[path = "../out/test_rust/sdodps.rs"]
mod sdodps;

use std::sync::Mutex;

#[test]
fn codec_matrix_round_trips_intel_motorola_float_and_enum() {
    use codec_matrix::*;

    let mut intel = MatrixIntelTypes::new();
    intel.set_u8(0xa5).unwrap();
    intel.set_s8(-42).unwrap();
    intel.set_u12(0x0bce).unwrap();
    intel.set_s12(112.0).unwrap();
    intel.set_state(MatrixState::Error).unwrap();
    intel
        .set_inline_enum(MatrixIntelTypesInlineEnumValue::Two)
        .unwrap();
    intel.set_opcode(MatrixOpcode::SetReq).unwrap();
    assert_eq!(intel.get_u8().unwrap(), 0xa5);
    assert_eq!(intel.get_s8().unwrap(), -42);
    assert_eq!(intel.get_u12().unwrap(), 0x0bce);
    assert!((intel.get_s12().unwrap() - 112.0).abs() < 1e-6);
    assert_eq!(intel.get_state().unwrap(), MatrixState::Error);
    assert_eq!(
        intel.get_inline_enum().unwrap(),
        MatrixIntelTypesInlineEnumValue::Two
    );
    assert_eq!(intel.get_opcode().unwrap(), MatrixOpcode::SetReq);
    assert_eq!(MatrixOpcode::WriteReq, MatrixOpcode::SetReq);

    let mut collision = MatrixCollision::new();
    collision.set_state(MatrixCollisionValue::One).unwrap();
    assert_eq!(collision.get_state().unwrap(), MatrixCollisionValue::One);

    let mut motorola = MatrixMotorolaTypes::new();
    motorola.set_u8_be(0x5a).unwrap();
    motorola.set_s8_be(-17).unwrap();
    motorola.set_u12_be(0x456).unwrap();
    motorola.set_s12_be(87.0).unwrap();
    assert_eq!(motorola.get_u8_be().unwrap(), 0x5a);
    assert_eq!(motorola.get_s8_be().unwrap(), -17);
    assert_eq!(motorola.get_u12_be().unwrap(), 0x456);
    assert!((motorola.get_s12_be().unwrap() - 87.0).abs() < 1e-6);

    let mut float_message = MatrixFloat::new();
    float_message.set_f32(-7.25).unwrap();
    float_message.set_raw32(0x89ab_cdef).unwrap();
    assert_eq!(float_message.get_f32().unwrap(), -7.25);
    assert_eq!(float_message.get_raw32().unwrap(), 0x89ab_cdef);

    let mut double_message = MatrixDouble::new();
    double_message.set_d64(9876.54321).unwrap();
    assert!((double_message.get_d64().unwrap() - 9876.54321).abs() < 1e-12);
}

#[test]
fn message_catalog_and_typed_message_getters_work() {
    use codec_matrix::*;

    assert_eq!(get_all_mess().len(), 8);
    assert_eq!(
        get_message(CAN_ID_MATRIXINTELTYPES).map(|message| message.dlc),
        Some(8)
    );
    assert_eq!(message_dlc(0xffff_ffff), None);
    assert_eq!(
        get_all_signals(CAN_ID_MATRIXINTELTYPES).map(<[_]>::len),
        Some(7)
    );
    assert_eq!(
        get_signal(CAN_ID_MATRIXINTELTYPES, "u12").map(|signal| signal.bit_length),
        Some(12)
    );

    let decoded = decode_message(CAN_ID_MATRIXINTELTYPES, 0, 8).unwrap();
    assert!(decoded.get_matrixinteltypes().is_some());
    assert!(decoded.get_matrixdouble().is_none());
    assert!(matches!(
        decode_message(CAN_ID_MATRIXINTELTYPES, 0, 7),
        Err(DbccError::InvalidDlc { .. })
    ));
}

#[test]
fn bitfield_edges_and_multiplex_guards_work() {
    use bitfield_edge::*;

    let mut packed = EdgePacked::new();
    packed.set_unsigned12(0xabc).unwrap();
    packed.set_signed8(-17).unwrap();
    packed.set_unsigned5(0x15).unwrap();
    packed.set_signed3(-3).unwrap();
    packed.set_flag0(1).unwrap();
    packed.set_flag3(1).unwrap();
    assert_eq!(packed.get_unsigned12().unwrap(), 0xabc);
    assert_eq!(packed.get_signed8().unwrap(), -17);
    assert_eq!(packed.get_unsigned5().unwrap(), 0x15);
    assert_eq!(packed.get_signed3().unwrap(), -3);
    assert_eq!(packed.get_flag0().unwrap(), 1);
    assert_eq!(packed.get_flag3().unwrap(), 1);

    let mut mux = EdgeMux::new();
    mux.set_mux(1).unwrap();
    mux.set_muxed_a(0x5a).unwrap();
    assert_eq!(mux.get_muxed_a().unwrap(), 0x5a);
    assert!(matches!(
        mux.get_muxed_b(),
        Err(DbccError::InactiveMultiplexedSignal { .. })
    ));
}

static SDO_FRAMES: Mutex<Vec<sdodps::CanFrame>> = Mutex::new(Vec::new());

fn capture_sdo_frame(id: u32, dlc: u8, payload: u64) -> bool {
    SDO_FRAMES
        .lock()
        .unwrap()
        .push(sdodps::CanFrame { id, dlc, payload });
    true
}

fn read_hash() -> Option<u32> {
    Some(0x1234_5678)
}

fn read_kp() -> Option<f32> {
    Some(12.5)
}

#[test]
fn sdo_get_all_getters_and_float_sigval_work() {
    use sdodps::*;

    SDO_FRAMES.lock().unwrap().clear();
    let mut master = SdoMaster::new();
    master.set_tx_callback(capture_sdo_frame);
    assert!(master.get_all_mess());
    let frames = SDO_FRAMES.lock().unwrap();
    assert_eq!(frames.len(), 2);
    assert!(frames.iter().all(|frame| frame.payload & 0xff == 3));
    drop(frames);

    let mut slave = PcuSdoSlave::new();
    slave.set_tx_callback(capture_sdo_frame);
    slave.set_dbc_hash_reader(read_hash);
    slave.set_kp_batt_reader(read_kp);

    master.set_expected_pcu_hash(0x1234_5678);
    SDO_FRAMES.lock().unwrap().clear();
    assert!(slave.notify(PcuVar::DbcHash));
    let hash_response = SDO_FRAMES.lock().unwrap().pop().unwrap();
    assert!(master.process(hash_response.id, hash_response.payload));
    assert!(master.pcu_hash_verified());
    assert_eq!(master.get_pcu_dbc_hash(), Some(0x1234_5678));

    assert!(slave.notify(PcuVar::KpBatt));
    let kp_response = SDO_FRAMES.lock().unwrap().pop().unwrap();
    assert!(master.process(kp_response.id, kp_response.payload));
    assert_eq!(master.get_pcu_kp_batt(), Some(12.5));
    assert_eq!(master.take_pcu_kp_batt(), Some(12.5));
    assert_eq!(master.get_pcu_kp_batt(), None);

    SDO_FRAMES.lock().unwrap().clear();
    assert!(slave.process(CAN_ID_SDOPCU, SdoOpcode::GetAllReq as u64));
    assert_eq!(SDO_FRAMES.lock().unwrap().len(), PcuVar::ALL.len());
}
