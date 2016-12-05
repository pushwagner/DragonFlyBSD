/*-
 * Copyright (c) 1997, Stefan Esser <se@freebsd.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: src/sys/dev/pci/pcireg.h,v 1.64.2.4.2.1 2009/04/15 03:14:26 kensmith Exp $
 */

#ifndef _PCIREG_H_
#define _PCIREG_H_

#ifndef _SYS_TYPES_H_
#include <sys/types.h>
#endif

typedef u_int16_t pci_vendor_id_t;
typedef u_int16_t pci_product_id_t;
typedef u_int8_t pci_class_t;
typedef u_int8_t pci_subclass_t;
typedef u_int8_t pci_interface_t;
typedef u_int8_t pci_revision_t;
typedef u_int8_t pci_intr_pin_t;
typedef u_int8_t pci_intr_line_t;
typedef u_int32_t pcireg_t;             /* ~typical configuration space */

/*
 * PCIM_xxx: mask to locate subfield in register
 * PCIR_xxx: config register offset
 * PCIC_xxx: device class
 * PCIS_xxx: device subclass
 * PCIP_xxx: device programming interface
 * PCIV_xxx: PCI vendor ID (only required to fixup ancient devices)
 * PCID_xxx: device ID
 * PCIY_xxx: capability identification number
 * PCIZ_xxx: extended capability identification number
 */

/* some PCI bus constants */

#define	PCI_BUSMAX	255
#define	PCI_SLOTMAX	31
#define	PCI_FUNCMAX	7
#define	PCI_REGMAX	255
#define	PCIE_REGMAX	4095
#define	PCI_MAXHDRTYPE	2

/* PCI config header registers for all devices */

#define	PCIR_DEVVENDOR	0x00
#define	PCIR_VENDOR	0x00
#define	PCIR_DEVICE	0x02
#define	PCIR_COMMAND	0x04
#define PCIR_CARDBUSCIS 0x28
#define	PCIM_CMD_PORTEN		0x0001
#define	PCIM_CMD_MEMEN		0x0002
#define	PCIM_CMD_BUSMASTEREN	0x0004
#define	PCIM_CMD_SPECIALEN	0x0008
#define	PCIM_CMD_MWRICEN	0x0010
#define	PCIM_CMD_PERRESPEN	0x0040
#define	PCIM_CMD_SERRESPEN	0x0100
#define	PCIM_CMD_BACKTOBACK	0x0200
#define	PCIM_CMD_INTxDIS	0x0400
#define	PCIR_STATUS	0x06
#define PCIM_STATUS_INTxSTATE	0x0008
#define	PCIM_STATUS_CAPPRESENT	0x0010
#define	PCIM_STATUS_66CAPABLE	0x0020
#define	PCIM_STATUS_BACKTOBACK	0x0080
#define	PCIM_STATUS_PERRREPORT	0x0100
#define	PCIM_STATUS_SEL_FAST	0x0000
#define	PCIM_STATUS_SEL_MEDIMUM	0x0200
#define	PCIM_STATUS_SEL_SLOW	0x0400
#define	PCIM_STATUS_SEL_MASK	0x0600
#define	PCIM_STATUS_STABORT	0x0800
#define	PCIM_STATUS_RTABORT	0x1000
#define	PCIM_STATUS_RMABORT	0x2000
#define	PCIM_STATUS_SERR	0x4000
#define	PCIM_STATUS_PERR	0x8000
#define	PCIR_REVID	0x08
#define	PCIR_PROGIF	0x09
#define	PCIR_SUBCLASS	0x0a
#define	PCIR_CLASS	0x0b
#define	PCIR_CACHELNSZ	0x0c
#define	PCIR_LATTIMER	0x0d
#define	PCIR_HDRTYPE	0x0e
#define	PCIM_HDRTYPE		0x7f
#define	PCIM_HDRTYPE_NORMAL	0x00
#define	PCIM_HDRTYPE_BRIDGE	0x01
#define	PCIM_HDRTYPE_CARDBUS	0x02
#define	PCIM_MFDEV		0x80
#define	PCIR_BIST	0x0f

/* Capability Register Offsets */

#define	PCICAP_ID	0x0
#define	PCICAP_NEXTPTR	0x1

/* Capability Identification Numbers */

#define	PCIY_PMG	0x01	/* PCI Power Management */
#define	PCIY_AGP	0x02	/* AGP */
#define	PCIY_VPD	0x03	/* Vital Product Data */
#define	PCIY_SLOTID	0x04	/* Slot Identification */
#define	PCIY_MSI	0x05	/* Message Signaled Interrupts */
#define	PCIY_CHSWP	0x06	/* CompactPCI Hot Swap */
#define	PCIY_PCIX	0x07	/* PCI-X */
#define	PCIY_HT		0x08	/* HyperTransport */
#define	PCIY_VENDOR	0x09	/* Vendor Unique */
#define	PCIY_DEBUG	0x0a	/* Debug port */
#define	PCIY_CRES	0x0b	/* CompactPCI central resource control */
#define	PCIY_HOTPLUG	0x0c	/* PCI Hot-Plug */
#define	PCIY_SUBVENDOR	0x0d	/* PCI-PCI bridge subvendor ID */
#define	PCIY_AGP8X	0x0e	/* AGP 8x */
#define	PCIY_SECDEV	0x0f	/* Secure Device */
#define	PCIY_EXPRESS	0x10	/* PCI Express */
#define	PCIY_MSIX	0x11	/* MSI-X */
#define	PCIY_SATA	0x12	/* SATA */
#define	PCIY_PCIAF	0x13	/* PCI Advanced Features */

/* Extended Capability Register Fields */

#define	PCIR_EXTCAP	0x100
#define	PCIM_EXTCAP_ID		0x0000ffff
#define	PCIM_EXTCAP_VER		0x000f0000
#define	PCIM_EXTCAP_NEXTPTR	0xfff00000
#define	PCI_EXTCAP_ID(ecap)	((ecap) & PCIM_EXTCAP_ID)
#define	PCI_EXTCAP_VER(ecap)	(((ecap) & PCIM_EXTCAP_VER) >> 16)
#define	PCI_EXTCAP_NEXTPTR(ecap) (((ecap) & PCIM_EXTCAP_NEXTPTR) >> 20)

/* Extended Capability Identification Numbers */

#define	PCIZ_AER	0x0001	/* Advanced Error Reporting */
#define	PCIZ_VC		0x0002	/* Virtual Channel */
#define	PCIZ_SERNUM	0x0003	/* Device Serial Number */
#define	PCIZ_PWRBDGT	0x0004	/* Power Budgeting */
#define	PCIZ_VENDOR	0x000b	/* Vendor Unique */
#define	PCIZ_ACS	0x000d	/* Access Control Services */
#define	PCIZ_ARI	0x000e	/* Alternative Routing-ID Interpretation */
#define	PCIZ_ATS	0x000f	/* Address Translation Services */
#define	PCIZ_SRIOV	0x0010	/* Single Root IO Virtualization */

/* config registers for header type 0 devices */

#define	PCIR_BARS	0x10
#define PCIR_MAPS       PCIR_BARS
#define	PCIR_BAR(x)		(PCIR_BARS + (x) * 4)
#define	PCIR_MAX_BAR_0		5
#define	PCI_RID2BAR(rid)	(((rid) - PCIR_BARS) / 4)
#define	PCI_BAR_IO(x)		(((x) & PCIM_BAR_SPACE) == PCIM_BAR_IO_SPACE)
#define	PCI_BAR_MEM(x)		(((x) & PCIM_BAR_SPACE) == PCIM_BAR_MEM_SPACE)
#define	PCIM_BAR_SPACE		0x00000001
#define	PCIM_BAR_MEM_SPACE	0
#define	PCIM_BAR_IO_SPACE	1
#define	PCIM_BAR_MEM_TYPE	0x00000006
#define	PCIM_BAR_MEM_32		0
#define	PCIM_BAR_MEM_1MB	2	/* Locate below 1MB in PCI <= 2.1 */
#define	PCIM_BAR_MEM_64		4
#define	PCIM_BAR_MEM_PREFETCH	0x00000008
#define	PCIM_BAR_MEM_BASE	0xfffffff0
#define	PCIM_BAR_IO_RESERVED	0x00000002
#define	PCIM_BAR_IO_BASE	0xfffffffc
#define	PCIR_CIS	0x28
#define	PCIM_CIS_ASI_MASK	0x7
#define	PCIM_CIS_ASI_CONFIG	0
#define	PCIM_CIS_ASI_BAR0	1
#define	PCIM_CIS_ASI_BAR1	2
#define	PCIM_CIS_ASI_BAR2	3
#define	PCIM_CIS_ASI_BAR3	4
#define	PCIM_CIS_ASI_BAR4	5
#define	PCIM_CIS_ASI_BAR5	6
#define	PCIM_CIS_ASI_ROM	7
#define	PCIM_CIS_ADDR_MASK	0x0ffffff8
#define	PCIM_CIS_ROM_MASK	0xf0000000
#define PCIM_CIS_CONFIG_MASK	0xff
#define	PCIR_SUBVEND_0	0x2c
#define	PCIR_SUBDEV_0	0x2e
#define	PCIR_BIOS	0x30
#define	PCIM_BIOS_ENABLE	0x01
#define	PCIM_BIOS_ADDR_MASK	0xfffff800
#define	PCIR_CAP_PTR	0x34
#define	PCIR_INTLINE	0x3c
#define	PCIR_INTPIN	0x3d
#define	PCIR_MINGNT	0x3e
#define	PCIR_MAXLAT	0x3f

/* config registers for header type 1 (PCI-to-PCI bridge) devices */

#define	PCIR_MAX_BAR_1	1
#define	PCIR_SECSTAT_1	0x1e

#define	PCIR_PRIBUS_1	0x18
#define	PCIR_SECBUS_1	0x19
#define	PCIR_SUBBUS_1	0x1a
#define	PCIR_SECLAT_1	0x1b

#define	PCIR_IOBASEL_1	0x1c
#define	PCIR_IOLIMITL_1	0x1d
#define	PCIR_IOBASEH_1	0x30
#define	PCIR_IOLIMITH_1	0x32
#define	PCIM_BRIO_16		0x0
#define	PCIM_BRIO_32		0x1
#define	PCIM_BRIO_MASK		0xf

#define	PCIR_MEMBASE_1	0x20
#define	PCIR_MEMLIMIT_1	0x22

#define	PCIR_PMBASEL_1	0x24
#define	PCIR_PMLIMITL_1	0x26
#define	PCIR_PMBASEH_1	0x28
#define	PCIR_PMLIMITH_1	0x2c
#define	PCIM_BRPM_32		0x0
#define	PCIM_BRPM_64		0x1
#define	PCIM_BRPM_MASK		0xf

#define	PCIR_BRIDGECTL_1 0x3e

/* config registers for header type 2 (CardBus) devices */

#define	PCIR_MAX_BAR_2	0
#define	PCIR_CAP_PTR_2	0x14
#define	PCIR_SECSTAT_2	0x16

#define	PCIR_PRIBUS_2	0x18
#define	PCIR_SECBUS_2	0x19
#define	PCIR_SUBBUS_2	0x1a
#define	PCIR_SECLAT_2	0x1b

#define	PCIR_MEMBASE0_2	0x1c
#define	PCIR_MEMLIMIT0_2 0x20
#define	PCIR_MEMBASE1_2	0x24
#define	PCIR_MEMLIMIT1_2 0x28
#define	PCIR_IOBASE0_2	0x2c
#define	PCIR_IOLIMIT0_2	0x30
#define	PCIR_IOBASE1_2	0x34
#define	PCIR_IOLIMIT1_2	0x38

#define	PCIR_BRIDGECTL_2 0x3e

#define	PCIR_SUBVEND_2	0x40
#define	PCIR_SUBDEV_2	0x42

#define	PCIR_PCCARDIF_2	0x44

/* PCI device class, subclass and programming interface definitions */

#define	PCIC_OLD	0x00
#define	PCIS_OLD_NONVGA		0x00
#define	PCIS_OLD_VGA		0x01

#define	PCIC_STORAGE	0x01
#define	PCIS_STORAGE_SCSI	0x00
#define	PCIS_STORAGE_IDE	0x01
#define	PCIP_STORAGE_IDE_MODEPRIM	0x01
#define	PCIP_STORAGE_IDE_PROGINDPRIM	0x02
#define	PCIP_STORAGE_IDE_MODESEC	0x04
#define	PCIP_STORAGE_IDE_PROGINDSEC	0x08
#define	PCIP_STORAGE_IDE_MASTERDEV	0x80
#define	PCIS_STORAGE_FLOPPY	0x02
#define	PCIS_STORAGE_IPI	0x03
#define	PCIS_STORAGE_RAID	0x04
#define	PCIS_STORAGE_ATA_ADMA	0x05
#define	PCIS_STORAGE_SATA	0x06
#define	PCIP_STORAGE_SATA_AHCI_1_0	0x01
#define	PCIS_STORAGE_SAS	0x07
#define PCIS_STORAGE_NVM	0x08
#define PCIP_STORAGE_NVM_NVMHCI_1_0		0x01
#define PCIP_STORAGE_NVM_ENTERPRISE_NVMHCI_1_0	0x02
#define	PCIS_STORAGE_OTHER	0x80

#define	PCIC_NETWORK	0x02
#define	PCIS_NETWORK_ETHERNET	0x00
#define	PCIS_NETWORK_TOKENRING	0x01
#define	PCIS_NETWORK_FDDI	0x02
#define	PCIS_NETWORK_ATM	0x03
#define	PCIS_NETWORK_ISDN	0x04
#define	PCIS_NETWORK_WORLDFIP	0x05
#define	PCIS_NETWORK_PICMG	0x06
#define	PCIS_NETWORK_OTHER	0x80

#define	PCIC_DISPLAY	0x03
#define	PCIS_DISPLAY_VGA	0x00
#define	PCIS_DISPLAY_XGA	0x01
#define	PCIS_DISPLAY_3D		0x02
#define	PCIS_DISPLAY_OTHER	0x80

#define	PCIC_MULTIMEDIA	0x04
#define	PCIS_MULTIMEDIA_VIDEO	0x00
#define	PCIS_MULTIMEDIA_AUDIO	0x01
#define	PCIS_MULTIMEDIA_TELE	0x02
#define	PCIS_MULTIMEDIA_HDA	0x03
#define	PCIS_MULTIMEDIA_OTHER	0x80

#define	PCIC_MEMORY	0x05
#define	PCIS_MEMORY_RAM		0x00
#define	PCIS_MEMORY_FLASH	0x01
#define	PCIS_MEMORY_OTHER	0x80

#define	PCIC_BRIDGE	0x06
#define	PCIS_BRIDGE_HOST	0x00
#define	PCIS_BRIDGE_ISA		0x01
#define	PCIS_BRIDGE_EISA	0x02
#define	PCIS_BRIDGE_MCA		0x03
#define	PCIS_BRIDGE_PCI		0x04
#define	PCIP_BRIDGE_PCI_SUBTRACTIVE	0x01
#define	PCIS_BRIDGE_PCMCIA	0x05
#define	PCIS_BRIDGE_NUBUS	0x06
#define	PCIS_BRIDGE_CARDBUS	0x07
#define	PCIS_BRIDGE_RACEWAY	0x08
#define	PCIS_BRIDGE_PCI_TRANSPARENT 0x09
#define	PCIS_BRIDGE_INFINIBAND	0x0a
#define	PCIS_BRIDGE_OTHER	0x80

#define	PCIC_SIMPLECOMM	0x07
#define	PCIS_SIMPLECOMM_UART	0x00
#define	PCIP_SIMPLECOMM_UART_8250	0x00
#define	PCIP_SIMPLECOMM_UART_16450A	0x01
#define	PCIP_SIMPLECOMM_UART_16550A	0x02
#define	PCIP_SIMPLECOMM_UART_16650A	0x03
#define	PCIP_SIMPLECOMM_UART_16750A	0x04
#define	PCIP_SIMPLECOMM_UART_16850A	0x05
#define	PCIP_SIMPLECOMM_UART_16950A	0x06
#define	PCIS_SIMPLECOMM_PAR	0x01
#define	PCIS_SIMPLECOMM_MULSER	0x02
#define	PCIS_SIMPLECOMM_MODEM	0x03
#define	PCIS_SIMPLECOMM_GPIB	0x04
#define	PCIS_SIMPLECOMM_SMART_CARD 0x05
#define	PCIS_SIMPLECOMM_OTHER	0x80

#define	PCIC_BASEPERIPH	0x08
#define	PCIS_BASEPERIPH_PIC	0x00
#define	PCIP_BASEPERIPH_PIC_8259A	0x00
#define	PCIP_BASEPERIPH_PIC_ISA		0x01
#define	PCIP_BASEPERIPH_PIC_EISA	0x02
#define	PCIP_BASEPERIPH_PIC_IO_APIC	0x10
#define	PCIP_BASEPERIPH_PIC_IOX_APIC	0x20
#define	PCIS_BASEPERIPH_DMA	0x01
#define	PCIS_BASEPERIPH_TIMER	0x02
#define	PCIS_BASEPERIPH_RTC	0x03
#define	PCIS_BASEPERIPH_PCIHOT	0x04
#define	PCIS_BASEPERIPH_SDHC	0x05
#define	PCIS_BASEPERIPH_OTHER	0x80

#define	PCIC_INPUTDEV	0x09
#define	PCIS_INPUTDEV_KEYBOARD	0x00
#define	PCIS_INPUTDEV_DIGITIZER	0x01
#define	PCIS_INPUTDEV_MOUSE	0x02
#define	PCIS_INPUTDEV_SCANNER	0x03
#define	PCIS_INPUTDEV_GAMEPORT	0x04
#define	PCIS_INPUTDEV_OTHER	0x80

#define	PCIC_DOCKING	0x0a
#define	PCIS_DOCKING_GENERIC	0x00
#define	PCIS_DOCKING_OTHER	0x80

#define	PCIC_PROCESSOR	0x0b
#define	PCIS_PROCESSOR_386	0x00
#define	PCIS_PROCESSOR_486	0x01
#define	PCIS_PROCESSOR_PENTIUM	0x02
#define	PCIS_PROCESSOR_ALPHA	0x10
#define	PCIS_PROCESSOR_POWERPC	0x20
#define	PCIS_PROCESSOR_MIPS	0x30
#define	PCIS_PROCESSOR_COPROC	0x40

#define	PCIC_SERIALBUS	0x0c
#define	PCIS_SERIALBUS_FW	0x00
#define	PCIS_SERIALBUS_ACCESS	0x01
#define	PCIS_SERIALBUS_SSA	0x02
#define	PCIS_SERIALBUS_USB	0x03
#define	PCIP_SERIALBUS_USB_UHCI		0x00
#define	PCIP_SERIALBUS_USB_OHCI		0x10
#define	PCIP_SERIALBUS_USB_EHCI		0x20
#define	PCIP_SERIALBUS_USB_XHCI		0x30
#define	PCIP_SERIALBUS_USB_DEVICE	0xfe
#define	PCIS_SERIALBUS_FC	0x04
#define	PCIS_SERIALBUS_SMBUS	0x05
#define	PCIS_SERIALBUS_INFINIBAND 0x06
#define	PCIS_SERIALBUS_IPMI	0x07
#define	PCIP_SERIALBUS_IPMI_SMIC	0x00
#define	PCIP_SERIALBUS_IPMI_KCS		0x01
#define	PCIP_SERIALBUS_IPMI_BT		0x02
#define	PCIS_SERIALBUS_SERCOS	0x08
#define	PCIS_SERIALBUS_CANBUS	0x09

#define	PCIC_WIRELESS	0x0d
#define	PCIS_WIRELESS_IRDA	0x00
#define	PCIS_WIRELESS_IR	0x01
#define	PCIS_WIRELESS_RF	0x10
#define	PCIS_WIRELESS_BLUETOOTH	0x11
#define	PCIS_WIRELESS_BROADBAND	0x12
#define	PCIS_WIRELESS_80211A	0x20
#define	PCIS_WIRELESS_80211B	0x21
#define	PCIS_WIRELESS_OTHER	0x80

#define	PCIC_INTELLIIO	0x0e
#define	PCIS_INTELLIIO_I2O	0x00

#define	PCIC_SATCOM	0x0f
#define	PCIS_SATCOM_TV		0x01
#define	PCIS_SATCOM_AUDIO	0x02
#define	PCIS_SATCOM_VOICE	0x03
#define	PCIS_SATCOM_DATA	0x04

#define	PCIC_CRYPTO	0x10
#define	PCIS_CRYPTO_NETCOMP	0x00
#define	PCIS_CRYPTO_ENTERTAIN	0x10
#define	PCIS_CRYPTO_OTHER	0x80

#define	PCIC_DASP	0x11
#define	PCIS_DASP_DPIO		0x00
#define	PCIS_DASP_PERFCNTRS	0x01
#define	PCIS_DASP_COMM_SYNC	0x10
#define	PCIS_DASP_MGMT_CARD	0x20
#define	PCIS_DASP_OTHER		0x80

#define	PCIC_OTHER	0xff

/* Bridge Control Values. */
#define	PCIB_BCR_PERR_ENABLE		0x0001
#define	PCIB_BCR_SERR_ENABLE		0x0002
#define	PCIB_BCR_ISA_ENABLE		0x0004
#define	PCIB_BCR_VGA_ENABLE		0x0008
#define	PCIB_BCR_MASTER_ABORT_MODE	0x0020
#define	PCIB_BCR_SECBUS_RESET		0x0040
#define	PCIB_BCR_SECBUS_BACKTOBACK	0x0080
#define	PCIB_BCR_PRI_DISCARD_TIMEOUT	0x0100
#define	PCIB_BCR_SEC_DISCARD_TIMEOUT	0x0200
#define	PCIB_BCR_DISCARD_TIMER_STATUS	0x0400
#define	PCIB_BCR_DISCARD_TIMER_SERREN	0x0800

/* PCI power manangement */
#define	PCIR_POWER_CAP		0x2
#define	PCIM_PCAP_SPEC			0x0007
#define	PCIM_PCAP_PMEREQCLK		0x0008
#define	PCIM_PCAP_PMEREQPWR		0x0010
#define	PCIM_PCAP_DEVSPECINIT		0x0020
#define	PCIM_PCAP_DYNCLOCK		0x0040
#define	PCIM_PCAP_SECCLOCK		0x00c0
#define	PCIM_PCAP_CLOCKMASK		0x00c0
#define	PCIM_PCAP_REQFULLCLOCK		0x0100
#define	PCIM_PCAP_D1SUPP		0x0200
#define	PCIM_PCAP_D2SUPP		0x0400
#define	PCIM_PCAP_D0PME			0x0800
#define	PCIM_PCAP_D1PME			0x1000
#define	PCIM_PCAP_D2PME			0x2000
#define	PCIM_PCAP_D3PME_HOT		0x4000
#define	PCIM_PCAP_D3PME_COLD		0x8000

#define	PCIR_POWER_STATUS	0x4
#define	PCIM_PSTAT_D0			0x0000
#define	PCIM_PSTAT_D1			0x0001
#define	PCIM_PSTAT_D2			0x0002
#define	PCIM_PSTAT_D3			0x0003
#define	PCIM_PSTAT_DMASK		0x0003
#define	PCIM_PSTAT_REPENABLE		0x0010
#define	PCIM_PSTAT_PMEENABLE		0x0100
#define	PCIM_PSTAT_D0POWER		0x0000
#define	PCIM_PSTAT_D1POWER		0x0200
#define	PCIM_PSTAT_D2POWER		0x0400
#define	PCIM_PSTAT_D3POWER		0x0600
#define	PCIM_PSTAT_D0HEAT		0x0800
#define	PCIM_PSTAT_D1HEAT		0x1000
#define	PCIM_PSTAT_D2HEAT		0x1200
#define	PCIM_PSTAT_D3HEAT		0x1400
#define	PCIM_PSTAT_DATAUNKN		0x0000
#define	PCIM_PSTAT_DATADIV10		0x2000
#define	PCIM_PSTAT_DATADIV100		0x4000
#define	PCIM_PSTAT_DATADIV1000		0x6000
#define	PCIM_PSTAT_DATADIVMASK		0x6000
#define	PCIM_PSTAT_PME			0x8000

#define	PCIR_POWER_PMCSR	0x6
#define	PCIM_PMCSR_DCLOCK		0x10
#define	PCIM_PMCSR_B2SUPP		0x20
#define	PCIM_BMCSR_B3SUPP		0x40
#define	PCIM_BMCSR_BPCE			0x80

#define	PCIR_POWER_DATA		0x7

/* VPD capability registers */
#define	PCIR_VPD_ADDR		0x2
#define	PCIR_VPD_DATA		0x4

/* PCI Message Signalled Interrupts (MSI) */
#define	PCIR_MSI_CTRL		0x2
#define	PCIM_MSICTRL_VECTOR		0x0100
#define	PCIM_MSICTRL_64BIT		0x0080
#define	PCIM_MSICTRL_MME_MASK		0x0070
#define	PCIM_MSICTRL_MME_1		0x0000
#define	PCIM_MSICTRL_MME_2		0x0010
#define	PCIM_MSICTRL_MME_4		0x0020
#define	PCIM_MSICTRL_MME_8		0x0030
#define	PCIM_MSICTRL_MME_16		0x0040
#define	PCIM_MSICTRL_MME_32		0x0050
#define	PCIM_MSICTRL_MMC_MASK		0x000E
#define	PCIM_MSICTRL_MMC_1		0x0000
#define	PCIM_MSICTRL_MMC_2		0x0002
#define	PCIM_MSICTRL_MMC_4		0x0004
#define	PCIM_MSICTRL_MMC_8		0x0006
#define	PCIM_MSICTRL_MMC_16		0x0008
#define	PCIM_MSICTRL_MMC_32		0x000A
#define	PCIM_MSICTRL_MSI_ENABLE		0x0001
#define	PCIR_MSI_ADDR		0x4
#define	PCIR_MSI_ADDR_HIGH	0x8
#define	PCIR_MSI_DATA		0x8
#define	PCIR_MSI_DATA_64BIT	0xc
#define	PCIR_MSI_MASK		0x10
#define	PCIR_MSI_PENDING	0x14

/* PCI-X definitions */

/* For header type 0 devices */
#define	PCIXR_COMMAND		0x2
#define	PCIXM_COMMAND_DPERR_E		0x0001	/* Data Parity Error Recovery */
#define	PCIXM_COMMAND_ERO		0x0002	/* Enable Relaxed Ordering */
#define	PCIXM_COMMAND_MAX_READ		0x000c	/* Maximum Burst Read Count */
#define	PCIXM_COMMAND_MAX_READ_512	0x0000
#define	PCIXM_COMMAND_MAX_READ_1024	0x0004
#define	PCIXM_COMMAND_MAX_READ_2048	0x0008
#define	PCIXM_COMMAND_MAX_READ_4096	0x000c
#define	PCIXM_COMMAND_MAX_SPLITS 	0x0070	/* Maximum Split Transactions */
#define	PCIXM_COMMAND_MAX_SPLITS_1	0x0000
#define	PCIXM_COMMAND_MAX_SPLITS_2	0x0010
#define	PCIXM_COMMAND_MAX_SPLITS_3	0x0020
#define	PCIXM_COMMAND_MAX_SPLITS_4	0x0030
#define	PCIXM_COMMAND_MAX_SPLITS_8	0x0040
#define	PCIXM_COMMAND_MAX_SPLITS_12	0x0050
#define	PCIXM_COMMAND_MAX_SPLITS_16	0x0060
#define	PCIXM_COMMAND_MAX_SPLITS_32	0x0070
#define	PCIXM_COMMAND_VERSION		0x3000
#define	PCIXR_STATUS		0x4
#define	PCIXM_STATUS_DEVFN		0x000000FF
#define	PCIXM_STATUS_BUS		0x0000FF00
#define	PCIXM_STATUS_64BIT		0x00010000
#define	PCIXM_STATUS_133CAP		0x00020000
#define	PCIXM_STATUS_SC_DISCARDED	0x00040000
#define	PCIXM_STATUS_UNEXP_SC		0x00080000
#define	PCIXM_STATUS_COMPLEX_DEV	0x00100000
#define	PCIXM_STATUS_MAX_READ		0x00600000
#define	PCIXM_STATUS_MAX_READ_512	0x00000000
#define	PCIXM_STATUS_MAX_READ_1024	0x00200000
#define	PCIXM_STATUS_MAX_READ_2048	0x00400000
#define	PCIXM_STATUS_MAX_READ_4096	0x00600000
#define	PCIXM_STATUS_MAX_SPLITS		0x03800000
#define	PCIXM_STATUS_MAX_SPLITS_1	0x00000000
#define	PCIXM_STATUS_MAX_SPLITS_2	0x00800000
#define	PCIXM_STATUS_MAX_SPLITS_3	0x01000000
#define	PCIXM_STATUS_MAX_SPLITS_4	0x01800000
#define	PCIXM_STATUS_MAX_SPLITS_8	0x02000000
#define	PCIXM_STATUS_MAX_SPLITS_12	0x02800000
#define	PCIXM_STATUS_MAX_SPLITS_16	0x03000000
#define	PCIXM_STATUS_MAX_SPLITS_32	0x03800000
#define	PCIXM_STATUS_MAX_CUM_READ	0x1C000000
#define	PCIXM_STATUS_RCVD_SC_ERR	0x20000000
#define	PCIXM_STATUS_266CAP		0x40000000
#define	PCIXM_STATUS_533CAP		0x80000000

/* For header type 1 devices (PCI-X bridges) */
#define	PCIXR_SEC_STATUS	0x2
#define	PCIXM_SEC_STATUS_64BIT		0x0001
#define	PCIXM_SEC_STATUS_133CAP		0x0002
#define	PCIXM_SEC_STATUS_SC_DISC	0x0004
#define	PCIXM_SEC_STATUS_UNEXP_SC	0x0008
#define	PCIXM_SEC_STATUS_SC_OVERRUN	0x0010
#define	PCIXM_SEC_STATUS_SR_DELAYED	0x0020
#define	PCIXM_SEC_STATUS_BUS_MODE	0x03c0
#define	PCIXM_SEC_STATUS_VERSION	0x3000
#define	PCIXM_SEC_STATUS_266CAP		0x4000
#define	PCIXM_SEC_STATUS_533CAP		0x8000
#define	PCIXR_BRIDGE_STATUS	0x4
#define	PCIXM_BRIDGE_STATUS_DEVFN	0x000000FF
#define	PCIXM_BRIDGE_STATUS_BUS		0x0000FF00
#define	PCIXM_BRIDGE_STATUS_64BIT	0x00010000
#define	PCIXM_BRIDGE_STATUS_133CAP	0x00020000
#define	PCIXM_BRIDGE_STATUS_SC_DISCARDED 0x00040000
#define	PCIXM_BRIDGE_STATUS_UNEXP_SC	0x00080000
#define	PCIXM_BRIDGE_STATUS_SC_OVERRUN	0x00100000
#define	PCIXM_BRIDGE_STATUS_SR_DELAYED	0x00200000
#define	PCIXM_BRIDGE_STATUS_DEVID_MSGCAP 0x20000000
#define	PCIXM_BRIDGE_STATUS_266CAP	0x40000000
#define	PCIXM_BRIDGE_STATUS_533CAP	0x80000000

/* HT (HyperTransport) Capability definitions */
#define	PCIR_HT_COMMAND		0x2
#define	PCIM_HTCMD_CAP_MASK		0xf800	/* Capability type. */
#define	PCIM_HTCAP_SLAVE		0x0000	/* 000xx */
#define	PCIM_HTCAP_HOST			0x2000	/* 001xx */
#define	PCIM_HTCAP_SWITCH		0x4000	/* 01000 */
#define	PCIM_HTCAP_INTERRUPT		0x8000	/* 10000 */
#define	PCIM_HTCAP_REVISION_ID		0x8800	/* 10001 */
#define	PCIM_HTCAP_UNITID_CLUMPING	0x9000	/* 10010 */
#define	PCIM_HTCAP_EXT_CONFIG_SPACE	0x9800	/* 10011 */
#define	PCIM_HTCAP_ADDRESS_MAPPING	0xa000	/* 10100 */
#define	PCIM_HTCAP_MSI_MAPPING		0xa800	/* 10101 */
#define	PCIM_HTCAP_DIRECT_ROUTE		0xb000	/* 10110 */
#define	PCIM_HTCAP_VCSET		0xb800	/* 10111 */
#define	PCIM_HTCAP_RETRY_MODE		0xc000	/* 11000 */
#define	PCIM_HTCAP_X86_ENCODING		0xc800	/* 11001 */

/* HT MSI Mapping Capability definitions. */
#define	PCIM_HTCMD_MSI_ENABLE		0x0001
#define	PCIM_HTCMD_MSI_FIXED		0x0002
#define	PCIR_HTMSI_ADDRESS_LO	0x4
#define	PCIR_HTMSI_ADDRESS_HI	0x8

/* PCI Vendor capability definitions */
#define	PCIR_VENDOR_LENGTH	0x2
#define	PCIR_VENDOR_DATA	0x3

/* PCI EHCI Debug Port definitions */
#define	PCIR_DEBUG_PORT		0x2
#define	PCIM_DEBUG_PORT_OFFSET		0x1FFF
#define	PCIM_DEBUG_PORT_BAR		0xe000

/* PCI-PCI Bridge Subvendor definitions */
#define	PCIR_SUBVENDCAP_ID	0x4

/* MSI-X definitions */
#define	PCIR_MSIX_CTRL		0x2
#define	PCIM_MSIXCTRL_MSIX_ENABLE	0x8000
#define	PCIM_MSIXCTRL_FUNCTION_MASK	0x4000
#define	PCIM_MSIXCTRL_TABLE_SIZE	0x07FF
#define	PCIR_MSIX_TABLE		0x4
#define	PCIR_MSIX_PBA		0x8
#define	PCIM_MSIX_BIR_MASK		0x7
#define	PCIM_MSIX_BIR_BAR_10		0
#define	PCIM_MSIX_BIR_BAR_14		1
#define	PCIM_MSIX_BIR_BAR_18		2
#define	PCIM_MSIX_BIR_BAR_1C		3
#define	PCIM_MSIX_BIR_BAR_20		4
#define	PCIM_MSIX_BIR_BAR_24		5
#define	PCIM_MSIX_VCTRL_MASK		0x1

/*
 * PCI Express definitions
 * According to
 * PCI Express base specification, REV. 1.0a
 */

/* PCI Express capabilities, 16bits */
#define PCIER_CAPABILITY	0x2
#define PCIEM_CAP_VER_MASK	0x000f	/* Version */
#define PCIEM_CAP_VER_1		0x0001
#define PCIEM_CAP_VER_2		0x0002
#define PCIEM_CAP_PORT_TYPE	0x00f0	/* Port type mask */
#define PCIEM_CAP_SLOT_IMPL	0x0100	/* Slot implemented,
					 * valid only for root port and
					 * switch downstream port
					 */
#define PCIEM_CAP_IRQ_MSGNO	0x3e00

/* PCI Express port types */
#define PCIE_END_POINT		0x0000	/* Endpoint device */
#define PCIE_LEG_END_POINT	0x0010	/* Legacy endpoint device */
#define PCIE_ROOT_PORT		0x0040	/* Root port */
#define PCIE_UP_STREAM_PORT	0x0050	/* Switch upstream port */
#define PCIE_DOWN_STREAM_PORT	0x0060	/* Switch downstream port */
#define PCIE_PCIE2PCI_BRIDGE	0x0070	/* PCI Express to PCI/PCI-X bridge */
#define PCIE_PCI2PCIE_BRIDGE	0x0080	/* PCI/PCI-X to PCI Express bridge */
#define PCIE_ROOT_END_POINT	0x0090	/* Root Complex Integrated Endpoint */
#define PCIE_ROOT_EVT_COLL	0x00a0	/* Root Complex Event Collector */

/* PCI Express device capabilities, 32bits */
#define PCIER_DEVCAP			0x04
#define PCIEM_DEVCAP_MAX_PAYLOAD	0x0007

/* PCI Express device control, 16bits */
#define PCIER_DEVCTRL			0x08
#define PCIEM_DEVCTL_RELAX_ORDER	0x0010	/* Enable Relaxed Ordering */
#define PCIEM_DEVCTL_MAX_PAYLOAD_MASK	0x00e0	/* Max Payload Size */
#define PCIEM_DEVCTL_MAX_PAYLOAD_128	0x0000
#define PCIEM_DEVCTL_MAX_PAYLOAD_256	0x0020
#define PCIEM_DEVCTL_MAX_PAYLOAD_512	0x0040
#define PCIEM_DEVCTL_MAX_PAYLOAD_1024	0x0060
#define PCIEM_DEVCTL_MAX_PAYLOAD_2048	0x0080
#define PCIEM_DEVCTL_MAX_PAYLOAD_4096	0x00a0
#define PCIEM_DEVCTL_NOSNOOP		0x0800	/* Enable No Snoop */
#define PCIEM_DEVCTL_MAX_READRQ_MASK	0x7000	/* Max read request size */
#define PCIEM_DEVCTL_MAX_READRQ_128	0x0000
#define PCIEM_DEVCTL_MAX_READRQ_256	0x1000
#define PCIEM_DEVCTL_MAX_READRQ_512	0x2000
#define PCIEM_DEVCTL_MAX_READRQ_1024	0x3000
#define PCIEM_DEVCTL_MAX_READRQ_2048	0x4000
#define PCIEM_DEVCTL_MAX_READRQ_4096	0x5000

/* PCI Express device status, 16bits */
#define PCIER_DEVSTS			0x0a
#define PCIEM_DEVSTS_CORR_ERR		0x1	/* Correctable Error */
#define PCIEM_DEVSTS_NFATAL_ERR		0x2	/* Non-Fatal Error */
#define PCIEM_DEVSTS_FATAL_ERR		0x4	/* Fatal Error */
#define PCIEM_DEVSTS_UNSUPP_REQ		0x8	/* Unsupported Request */

/* PCI Express link capabilities, 32bits */
#define PCIER_LINKCAP			0x0c
#define PCIER_LINK_CAP2			0x2c
#define PCIEM_LNKCAP_SPEED_MASK		0x000f	/* Supported link speeds */
#define PCIEM_LNKCAP_SPEED_2_5		0x1	/* 2.5GT/s */
#define PCIEM_LNKCAP_SPEED_5		0x2	/* 5.0GT/s and 2.5GT/s */
#define PCIEM_LNKCAP_MAXW_MASK		0x03f0	/* Maximum link width */
#define PCIEM_LNKCAP_MAXW_X1		0x0010
#define PCIEM_LNKCAP_MAXW_X2		0x0020
#define PCIEM_LNKCAP_MAXW_X4		0x0040
#define PCIEM_LNKCAP_MAXW_X8		0x0080
#define PCIEM_LNKCAP_MAXW_X12		0x00c0
#define PCIEM_LNKCAP_MAXW_X16		0x0100
#define PCIEM_LNKCAP_MAXW_X32		0x0200
#define PCIEM_LNKCAP_ASPM_MASK		0x0c00	/* ASPM */
#define PCIEM_LNKCAP_ASPM_L0S		0x0400
#define PCIEM_LNKCAP_ASPM_L1		0x0c00

/* PCI Express link control, 32bits */
#define PCIER_LINKCTRL			0x10
#define PCIEM_LNKCTL_ASPM_MASK		0x3	/* ASPM */
#define PCIEM_LNKCTL_ASPM_DISABLE	0x0
#define PCIEM_LNKCTL_ASPM_L0S		0x1
#define PCIEM_LNKCTL_ASPM_L1		0x2
#define PCIEM_LNKCTL_RCB		0x8
#define PCIEM_LNKCTL_LINK_DIS		0x0010
#define PCIEM_LNKCTL_RETRAIN_LINK	0x0020
#define PCIEM_LNKCTL_COMMON_CLOCK	0x0040
#define PCIEM_LNKCTL_EXTENDED_SYNC	0x0080
#define PCIEM_LNKCTL_ECPM		0x0100
#define PCIEM_LNKCTL_HAWD		0x0200
#define PCIEM_LNKCTL_LBMIE		0x0400
#define PCIEM_LNKCTL_LABIE		0x0800

/* PCI Express link status, 16bits */
#define PCIER_LINKSTAT			0x12
#define PCIEM_LNKSTAT_WIDTH		0x03f0

/* PCI Express slot capabilities, 32bits */
#define PCIER_SLOTCAP		0x14
#define PCIEM_SLTCAP_ATTEN_BTN	0x00000001 /* Attention button present */
#define PCIEM_SLTCAP_PWR_CTRL	0x00000002 /* Power controller present */
#define PCIEM_SLTCAP_MRL_SNS	0x00000004 /* MRL sensor present */
#define PCIEM_SLTCAP_ATTEN_IND	0x00000008 /* Attention indicator present */
#define PCIEM_SLTCAP_PWR_IND	0x00000010 /* Power indicator present */
#define PCIEM_SLTCAP_HP_SURP	0x00000020 /* Hot-Plug surprise */
#define PCIEM_SLTCAP_HP_CAP	0x00000040 /* Hot-Plug capable */
#define PCIEM_SLTCAP_HP_MASK	0x0000007f /* Hot-Plug related bits */

/* PCI Express slot control, 16bits */
#define PCIER_SLOTCTRL			0x18
#define PCIEM_SLTCTL_HPINTR_MASK	0x001f	/* Hot-plug interrupts mask */
#define PCIEM_SLTCTL_HPINTR_EN		0x0020	/* Enable hot-plug interrupts */

/* PCI Express hot-plug interrupts */
#define PCIE_HPINTR_ATTEN_BTN		0x0001	/* Attention button intr */
#define PCIE_HPINTR_PWR_FAULT		0x0002	/* Power fault intr */
#define PCIE_HPINTR_MRL_SNS		0x0004	/* MRL sensor changed intr */
#define PCIE_HPINTR_PRSN_DETECT		0x0008	/* Presence detect intr */
#define PCIE_HPINTR_CMD_COMPL		0x0010	/* Command completed intr */

/* PCI Advanced Features definitions */
#define	PCIR_PCIAF_CAP		0x3
#define	PCIM_PCIAFCAP_TP	0x01
#define	PCIM_PCIAFCAP_FLR	0x02
#define	PCIR_PCIAF_CTRL		0x4
#define	PCIR_PCIAFCTRL_FLR	0x01
#define	PCIR_PCIAF_STATUS	0x5
#define	PCIR_PCIAFSTATUS_TP	0x01

/* Advanced Error Reporting */
#define	PCIR_AER_UC_STATUS	0x04
#define	PCIM_AER_UC_TRAINING_ERROR	0x00000001
#define	PCIM_AER_UC_DL_PROTOCOL_ERROR	0x00000010
#define	PCIM_AER_UC_SURPRISE_LINK_DOWN	0x00000020
#define	PCIM_AER_UC_POISONED_TLP	0x00001000
#define	PCIM_AER_UC_FC_PROTOCOL_ERROR	0x00002000
#define	PCIM_AER_UC_COMPLETION_TIMEOUT	0x00004000
#define	PCIM_AER_UC_COMPLETER_ABORT	0x00008000
#define	PCIM_AER_UC_UNEXPECTED_COMPLETION 0x00010000
#define	PCIM_AER_UC_RECEIVER_OVERFLOW	0x00020000
#define	PCIM_AER_UC_MALFORMED_TLP	0x00040000
#define	PCIM_AER_UC_ECRC_ERROR		0x00080000
#define	PCIM_AER_UC_UNSUPPORTED_REQUEST	0x00100000
#define	PCIM_AER_UC_ACS_VIOLATION	0x00200000
#define	PCIR_AER_UC_MASK	0x08	/* Shares bits with UC_STATUS */
#define	PCIR_AER_UC_SEVERITY	0x0c	/* Shares bits with UC_STATUS */
#define	PCIR_AER_COR_STATUS	0x10
#define	PCIM_AER_COR_RECEIVER_ERROR	0x00000001
#define	PCIM_AER_COR_BAD_TLP		0x00000040
#define	PCIM_AER_COR_BAD_DLLP		0x00000080
#define	PCIM_AER_COR_REPLAY_ROLLOVER	0x00000100
#define	PCIM_AER_COR_REPLAY_TIMEOUT	0x00001000
#define	PCIM_AER_COR_ADVISORY_NF_ERROR	0x00002000
#define	PCIR_AER_COR_MASK	0x14	/* Shares bits with COR_STATUS */
#define	PCIR_AER_CAP_CONTROL	0x18
#define	PCIM_AER_FIRST_ERROR_PTR	0x0000001f
#define	PCIM_AER_ECRC_GEN_CAPABLE	0x00000020
#define	PCIM_AER_ECRC_GEN_ENABLE	0x00000040
#define	PCIM_AER_ECRC_CHECK_CAPABLE	0x00000080
#define	PCIM_AER_ECRC_CHECK_ENABLE	0x00000100
#define	PCIR_AER_HEADER_LOG	0x1c
#define	PCIR_AER_ROOTERR_CMD	0x2c	/* Only for root complex ports */
#define	PCIM_AER_ROOTERR_COR_ENABLE	0x00000001
#define	PCIM_AER_ROOTERR_NF_ENABLE	0x00000002
#define	PCIM_AER_ROOTERR_F_ENABLE	0x00000004
#define	PCIR_AER_ROOTERR_STATUS	0x30	/* Only for root complex ports */
#define	PCIM_AER_ROOTERR_COR_ERR	0x00000001
#define	PCIM_AER_ROOTERR_MULTI_COR_ERR	0x00000002
#define	PCIM_AER_ROOTERR_UC_ERR		0x00000004
#define	PCIM_AER_ROOTERR_MULTI_UC_ERR	0x00000008
#define	PCIM_AER_ROOTERR_FIRST_UC_FATAL	0x00000010
#define	PCIM_AER_ROOTERR_NF_ERR		0x00000020
#define	PCIM_AER_ROOTERR_F_ERR		0x00000040
#define	PCIM_AER_ROOTERR_INT_MESSAGE	0xf8000000
#define	PCIR_AER_COR_SOURCE_ID	0x34	/* Only for root complex ports */
#define	PCIR_AER_ERR_SOURCE_ID	0x36	/* Only for root complex ports */

/* Virtual Channel definitions */
#define	PCIR_VC_CAP1		0x04
#define	PCIM_VC_CAP1_EXT_COUNT		0x00000007
#define	PCIM_VC_CAP1_LOWPRI_EXT_COUNT	0x00000070
#define	PCIR_VC_CAP2		0x08
#define	PCIR_VC_CONTROL		0x0C
#define	PCIR_VC_STATUS		0x0E
#define	PCIR_VC_RESOURCE_CAP(n)	(0x10 + (n) * 0x0C)
#define	PCIR_VC_RESOURCE_CTL(n)	(0x14 + (n) * 0x0C)
#define	PCIR_VC_RESOURCE_STA(n)	(0x18 + (n) * 0x0C)

/* Serial Number definitions */
#define	PCIR_SERIAL_LOW		0x04
#define	PCIR_SERIAL_HIGH	0x08

#endif	/* _PCIREG_H_ */