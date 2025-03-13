

#define CANARD_DSDLC_INTERNAL
#include "../inc/uavcan.equipment.indication.BeepCommand.h"

#include <string.h>

#ifdef CANARD_DSDLC_TEST_BUILD
#include <test_helpers.h>
#endif

uint32_t uavcan_equipment_indication_BeepCommand_encode(struct uavcan_equipment_indication_BeepCommand* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
) {
    uint32_t bit_ofs = 0;
    memset(buffer, 0, UAVCAN_EQUIPMENT_INDICATION_BEEPCOMMAND_MAX_SIZE);
    _uavcan_equipment_indication_BeepCommand_encode(buffer, &bit_ofs, msg, 
#if CANARD_ENABLE_TAO_OPTION
    tao
#else
    true
#endif
    );
    return ((bit_ofs+7)/8);
}

/*
  return true if the decode is invalid
 */
bool uavcan_equipment_indication_BeepCommand_decode(const CanardRxTransfer* transfer, struct uavcan_equipment_indication_BeepCommand* msg) {
#if CANARD_ENABLE_TAO_OPTION
    if (transfer->tao && (transfer->payload_len > UAVCAN_EQUIPMENT_INDICATION_BEEPCOMMAND_MAX_SIZE)) {
        return true; /* invalid payload length */
    }
#endif
    uint32_t bit_ofs = 0;
    if (_uavcan_equipment_indication_BeepCommand_decode(transfer, &bit_ofs, msg,
#if CANARD_ENABLE_TAO_OPTION
    transfer->tao
#else
    true
#endif
    )) {
        return true; /* invalid payload */
    }

    const uint32_t byte_len = (bit_ofs+7U)/8U;
#if CANARD_ENABLE_TAO_OPTION
    // if this could be CANFD then the dlc could indicating more bytes than
    // we actually have
    if (!transfer->tao) {
        return byte_len > transfer->payload_len;
    }
#endif
    return byte_len != transfer->payload_len;
}

#ifdef CANARD_DSDLC_TEST_BUILD
struct uavcan_equipment_indication_BeepCommand sample_uavcan_equipment_indication_BeepCommand_msg(void) {

    struct uavcan_equipment_indication_BeepCommand msg;






    msg.frequency = random_float16_val();







    msg.duration = random_float16_val();





    return msg;

}
#endif
