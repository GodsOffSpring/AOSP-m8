typedef enum _HT_IOT_ACTION{
	HT_IOT_ACT_TX_USE_AMSDU_4K = 0x00000001,
	HT_IOT_ACT_TX_USE_AMSDU_8K = 0x00000002,
	HT_IOT_ACT_DECLARE_MCS13 = 0x00000004,
	HT_IOT_ACT_DISABLE_EDCA_TURBO = 0x00000008,
	HT_IOT_ACT_MGNT_USE_CCK_6M = 0x00000010,
	HT_IOT_ACT_CDD_FSYNC = 0x00000020,
	HT_IOT_ACT_PURE_N_MODE = 0x00000040,
}HT_IOT_ACTION_E, *PHT_IOT_ACTION_E;

