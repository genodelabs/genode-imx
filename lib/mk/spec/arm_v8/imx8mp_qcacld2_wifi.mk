REQUIRES := arm_v8a

include $(call select_from_repositories,lib/mk/wifi.inc)

TARGET_LIB_DIR := $(REP_DIR)/src/lib/imx8mp_qcacld2_wifi

LIBS    += imx_linux_generated imx_lx_emul

INC_DIR += $(TARGET_LIB_DIR)

SRC_CC  += dtb_helper.cc
SRC_CC  += lx_emul/random.cc

SRC_C   += $(notdir $(wildcard $(TARGET_LIB_DIR)/generated_dummies.c))

SRC_C   += lx_emul/common_dummies.c
SRC_C   += lx_emul/shadow/drivers/char/random.c
SRC_C   += lx_emul/shadow/fs/libfs.c
SRC_C   += lx_emul/shadow/mm/dmapool.c
SRC_C   += lx_emul/shadow/mm/page_alloc.c
SRC_C   += lx_emul/shadow/mm/vmalloc.c
SRC_C   += fixed-clock.c
SRC_C   += gpcv2.c
SRC_C   += gpio-mxc.c
SRC_C   += pinctrl.c
SRC_C   += regulator-fixed.c

CC_OPT_net/mac80211/trace += -I$(LX_SRC_DIR)/net/mac80211
CC_OPT_net/wireless/trace += -I$(LX_SRC_DIR)/net/wireless

CC_OPT += \
          -Wno-address \
          -Wno-cast-function-type \
          -Wno-dangling-pointer \
          -Wno-enum-conversion \
          -Wno-implicit-fallthrough \
          -Wno-maybe-uninitialized \
          -Wno-unused-variable \

CC_C_OPT += \
            -DCONFIG_QCA_WIFI_ISOC=0 \
            -DCONFIG_QCA_WIFI_2_0=1 \
            -D__linux__ \
            -DANI_LITTLE_BYTE_ENDIAN \
            -DADF_SUPPORT \
            -DAH_BYTE_ORDER=1234 \
            -DANI_COMPILER_TYPE_GCC \
            -DANI_LITTLE_BIT_ENDIAN \
            -DANI_LOGDUMP \
            -DANI_OS_TYPE_ANDROID=6 \
            -DATH_BUS_PM \
            -DATH_PERF_PWR_OFFLOAD \
            -DATH_SUPPORT_DFS \
            -DATH_SUPPORT_SHARED_IRQ \
            -DATH_SUPPORT_WAPI \
            -DBUILD_STRING="\"+\"" \
            -DCHECKSUM_OFFLOAD \
            -DCONFIG_AR6320_SUPPORT \
            -DCONFIG_FW_LOGS_BASED_ON_INI \
            -DCONFIG_HL_SUPPORT \
            -DCONFIG_NON_QC_PLATFORM \
            -DCONFIG_PERF_NON_QC_PLATFORM \
            -DCONFIG_PER_VDEV_TX_DESC_POOL \
            -DCONFIG_TX_DESC_HI_PRIO_RESERVE \
            -DDEBUG_HL_LOGGING \
            -DDEBUG_RX_RING_BUFFER \
            -DDHCP_SERVER_OFFLOAD \
            -DDOT11F_LITTLE_ENDIAN_HOST \
            -DFEATURE_BUS_BANDWIDTH \
            -DFEATURE_BUS_BANDWIDTH \
            -DFEATURE_BUS_BANDWIDTH \
            -DFEATURE_COEX_PTA_CONFIG_ENABLE \
            -DFEATURE_HL_GROUP_CREDIT_FLOW_CONTROL \
            -DFEATURE_OEM_DATA_SUPPORT \
            -DFEATURE_WLAN_CH144 \
            -DFEATURE_WLAN_CH_AVOID \
            -DFEATURE_WLAN_DIAG_SUPPORT \
            -DFEATURE_WLAN_DIAG_SUPPORT_CSR \
            -DFEATURE_WLAN_DIAG_SUPPORT_LIM \
            -DFEATURE_WLAN_DISABLE_CHANNEL_SWITCH \
            -DFEATURE_WLAN_ESE \
            -DFEATURE_WLAN_ESE_UPLOAD \
            -DFEATURE_WLAN_EXTSCAN \
            -DFEATURE_WLAN_FORCE_SAP_SCC \
            -DFEATURE_WLAN_LFR \
            -DFEATURE_WLAN_LPHB \
            -DFEATURE_WLAN_MCC_TO_SCC_SWITCH \
            -DFEATURE_WLAN_PAL_MEM_DISABLE \
            -DFEATURE_WLAN_PAL_TIMER_DISABLE \
            -DFEATURE_WLAN_RA_FILTERING \
            -DFEATURE_WLAN_SCAN_PNO \
            -DFEATURE_WLAN_STA_AP_MODE_DFS_DISABLE \
            -DFEATURE_WLAN_WAPI \
            -DHAL_SELF_STA_PER_BSS=1 \
            -DHDD_TRACE_RECORD \
            -DHIF_MBOX_SLEEP_WAR \
            -DHIF_RX_THREAD \
            -DHIF_SDIO \
            -DHTC_CRP_DEBUG \
            -DIGTK_OFFLOAD \
            -DLIM_TRACE_RECORD \
            -DLINUX_QCMBR \
            -DMDNS_OFFLOAD \
            -DMSM8976_TCP_PERF \
            -DOSIF_NEED_RX_PEER_ID \
            -DPANIC_ON_BUG \
            -DPTT_SOCK_SVC_ENABLE \
            -DQCA_COMPUTE_TX_DELAY \
            -DQCA_COMPUTE_TX_DELAY_PER_TID \
            -DQCA_CONFIG_SMP \
            -DQCA_FEATURE_RPS \
            -DQCA_IBSS_SUPPORT \
            -DQCA_LL_TX_FLOW_CT \
            -DQCA_SUPPORT_TXRX_DRIVER_TCP_DEL_ACK \
            -DQCA_SUPPORT_TXRX_DRIVER_TCP_DEL_ACK \
            -DQCA_SUPPORT_TXRX_HL_BUNDLE \
            -DQCA_SUPPORT_TXRX_LOCAL_PEER_ID \
            -DQCA_SUPPORT_TX_THROTTLE \
            -DQCA_TXRX_PERF \
            -DQCA_WIFI_FTM \
            -DQC_WLAN_CHIPSET_QCA_CLD \
            -DSDIO_3_0 \
            -DSME_TRACE_RECORD \
            -DSOFTAP_CHANNEL_RANGE \
            -DTARGET_DUMP_FOR_NON_QC_PLATFORM \
            -DTARGET_RAMDUMP_AFTER_KERNEL_PANIC \
            -DTRACE_RECORD \
            -DTX_COMPLETION_THREAD \
            -DWCN_PRONTO \
            -DWCN_PRONTO_V1 \
            -DWDI_EVENT_ENABLE \
            -DWLANTL_DEBUG \
            -DWLAN_ACTIVEMODE_OFFLOAD_FEATURE \
            -DWLAN_AP_STA_CONCURRENCY \
            -DWLAN_AUTOGEN_MACADDR_FEATURE \
            -DWLAN_ENABLE_AGEIE_ON_SCAN_RESULTS \
            -DWLAN_ENABLE_CHNL_MATRIX_RESTRICTION \
            -DWLAN_ENABLE_SOCIAL_CHANNELS_5G_ONLY \
            -DWLAN_FEATURE_11AC \
            -DWLAN_FEATURE_11W \
            -DWLAN_FEATURE_APFIND \
            -DWLAN_FEATURE_FILS_SK \
            -DWLAN_FEATURE_GPIO_LED_FLASHING \
            -DWLAN_FEATURE_GTK_OFFLOAD \
            -DWLAN_FEATURE_GTK_OFFLOAD \
            -DWLAN_FEATURE_LINK_LAYER_STATS \
            -DWLAN_FEATURE_MBSSID \
            -DWLAN_FEATURE_MOTION_DETECTION \
            -DWLAN_FEATURE_NEIGHBOR_ROAMING \
            -DWLAN_FEATURE_NEIGHBOR_ROAMING_DEBUG \
            -DWLAN_FEATURE_P2P \
            -DWLAN_FEATURE_P2P_DEBUG \
            -DWLAN_FEATURE_PACKET_FILTERING \
            -DWLAN_FEATURE_ROAM_SCAN_OFFLOAD \
            -DWLAN_FEATURE_SAE \
            -DWLAN_FEATURE_SAP_TO_FOLLOW_STA_CHAN \
            -DWLAN_FEATURE_STATS_EXT \
            -DWLAN_FEATURE_VOWIFI \
            -DWLAN_FEATURE_VOWIFI_11R \
            -DWLAN_FEATURE_VOWIFI_11R_DEBUG \
            -DWLAN_FEATURE_WFD \
            -DWLAN_FEATURE_WOW_PULSE \
            -DWLAN_KD_READY_NOTIFIER \
            -DWLAN_LOGGING_SOCK_SVC_ENABLE \
            -DWLAN_NS_OFFLOAD \
            -DWLAN_OPEN_SOURCE \
            -DWLAN_PERF \
            -DWLAN_SOFTAP_VSTA_FEATURE \
            -DWLAN_VOWIFI_DEBUG \
            -DWLAN_WAKEUP_EVENTS \
            -DWLAN_WAPI_MODE_11AC_DISABLE \
            -DWMI_COEX_BTC_DUTYCYCLE \
            -DWMI_INTERFACE_EVENT_LOGGING

CC_C_OPT += \
            -I$(LX_SRC_DIR)/qca/CORE/CLD_TXRX/HTT \
            -I$(LX_SRC_DIR)/qca/CORE/CLD_TXRX/TLSHIM \
            -I$(LX_SRC_DIR)/qca/CORE/CLD_TXRX/TXRX \
            -I$(LX_SRC_DIR)/qca/CORE/EPPING/inc \
            -I$(LX_SRC_DIR)/qca/CORE/HDD/inc \
            -I$(LX_SRC_DIR)/qca/CORE/HDD/src \
            -I$(LX_SRC_DIR)/qca/CORE/MAC/inc \
            -I$(LX_SRC_DIR)/qca/CORE/MAC/src/dph \
            -I$(LX_SRC_DIR)/qca/CORE/MAC/src/include \
            -I$(LX_SRC_DIR)/qca/CORE/MAC/src/pe/include \
            -I$(LX_SRC_DIR)/qca/CORE/MAC/src/pe/lim \
            -I$(LX_SRC_DIR)/qca/CORE/MAC/src/pe/nan \
            -I$(LX_SRC_DIR)/qca/CORE/SAP/inc \
            -I$(LX_SRC_DIR)/qca/CORE/SAP/src \
            -I$(LX_SRC_DIR)/qca/CORE/SERVICES/BMI \
            -I$(LX_SRC_DIR)/qca/CORE/SERVICES/COMMON \
            -I$(LX_SRC_DIR)/qca/CORE/SERVICES/COMMON/adf \
            -I$(LX_SRC_DIR)/qca/CORE/SERVICES/COMMON/adf/linux \
            -I$(LX_SRC_DIR)/qca/CORE/SERVICES/COMMON/asf \
            -I$(LX_SRC_DIR)/qca/CORE/SERVICES/DFS/inc \
            -I$(LX_SRC_DIR)/qca/CORE/SERVICES/DFS/inc \
            -I$(LX_SRC_DIR)/qca/CORE/SERVICES/DFS/src \
            -I$(LX_SRC_DIR)/qca/CORE/SERVICES/DFS/src \
            -I$(LX_SRC_DIR)/qca/CORE/SERVICES/HIF \
            -I$(LX_SRC_DIR)/qca/CORE/SERVICES/HIF/common \
            -I$(LX_SRC_DIR)/qca/CORE/SERVICES/HIF/sdio \
            -I$(LX_SRC_DIR)/qca/CORE/SERVICES/HIF/sdio/linux \
            -I$(LX_SRC_DIR)/qca/CORE/SERVICES/HIF/sdio/linux/native_sdio/include \
            -I$(LX_SRC_DIR)/qca/CORE/SERVICES/HIF/sdio/linux/native_sdio/src \
            -I$(LX_SRC_DIR)/qca/CORE/SERVICES/HTC \
            -I$(LX_SRC_DIR)/qca/CORE/SERVICES/WMA \
            -I$(LX_SRC_DIR)/qca/CORE/SERVICES/WMI \
            -I$(LX_SRC_DIR)/qca/CORE/SME/inc \
            -I$(LX_SRC_DIR)/qca/CORE/SME/src/csr \
            -I$(LX_SRC_DIR)/qca/CORE/SVC/external \
            -I$(LX_SRC_DIR)/qca/CORE/SVC/inc \
            -I$(LX_SRC_DIR)/qca/CORE/SYS/common/inc \
            -I$(LX_SRC_DIR)/qca/CORE/SYS/legacy/src/pal/inc \
            -I$(LX_SRC_DIR)/qca/CORE/SYS/legacy/src/platform/inc \
            -I$(LX_SRC_DIR)/qca/CORE/SYS/legacy/src/system/inc \
            -I$(LX_SRC_DIR)/qca/CORE/SYS/legacy/src/utils/inc \
            -I$(LX_SRC_DIR)/qca/CORE/TL/inc \
            -I$(LX_SRC_DIR)/qca/CORE/UTILS/FWLOG \
            -I$(LX_SRC_DIR)/qca/CORE/UTILS/PKTLOG/include \
            -I$(LX_SRC_DIR)/qca/CORE/UTILS/PKTLOG/include \
            -I$(LX_SRC_DIR)/qca/CORE/VOSS/inc \
            -I$(LX_SRC_DIR)/qca/CORE/VOSS/src \
            -I$(LX_SRC_DIR)/qca/CORE/WDA/inc \
            -I$(LX_SRC_DIR)/qca/CORE/WDA/inc/legacy \
            -I$(LX_SRC_DIR)/qca/CORE/WDA/src \
            -I$(LX_SRC_DIR)/qca/CORE/WDI/CP/inc/ \
            -I$(LX_SRC_DIR)/qca/CORE/WDI/DP/inc/ \
            -I$(LX_SRC_DIR)/qca/CORE/WDI/TRP/CTS/inc/ \
            -I$(LX_SRC_DIR)/qca/CORE/WDI/TRP/DTS/inc/ \
            -I$(LX_SRC_DIR)/qca/CORE/WDI/WPAL/inc \
            -I$(LX_SRC_DIR)/qca/wcnss/inc \
            -I$(LX_SRC_DIR)/qca

vpath lx_emul/common_dummies.c $(REP_DIR)/src/lib/imx
vpath %.c  $(TARGET_LIB_DIR)
vpath %.cc $(TARGET_LIB_DIR)

DRIVER := wifi
BOARDS := mnt_pocket
DTS_PATH(mnt_pocket) := arch/arm64/boot/dts/freescale/imx8mp-mnt-pocket-reform.dts
DTS_EXTRACT(mnt_pocket) := --select usdhc2
