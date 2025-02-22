TOP = ../..
SUBDIR =

include $(TOP)/config.mk

ASN1_SOURCE = ../rrlp-components.asn ../rrlp-messages.asn

ASN_MODULE_SOURCE=	\
	VelocityEstimate.c	\
	ExtensionContainer.c	\
	Ext-GeographicalInformation.c	\
	MsrPosition-Req.c	\
	MsrPosition-Rsp.c	\
	AssistanceData.c	\
	ProtocolError.c	\
	PositionInstruct.c	\
	MethodType.c	\
	AccuracyOpt.c	\
	Accuracy.c	\
	PositionMethod.c	\
	MeasureResponseTime.c	\
	UseMultipleSets.c	\
	EnvironmentCharacter.c	\
	ReferenceAssistData.c	\
	BTSPosition.c	\
	BCCHCarrier.c	\
	BSIC.c	\
	TimeSlotScheme.c	\
	ModuloTimeSlot.c	\
	MsrAssistData.c	\
	SeqOfMsrAssistBTS.c	\
	MsrAssistBTS.c	\
	MultiFrameOffset.c	\
	RoughRTD.c	\
	SystemInfoAssistData.c	\
	SeqOfSystemInfoAssistBTS.c	\
	SystemInfoAssistBTS.c	\
	AssistBTSData.c	\
	CalcAssistanceBTS.c	\
	ReferenceWGS84.c	\
	FineRTD.c	\
	RelDistance.c	\
	RelativeAlt.c	\
	MultipleSets.c	\
	ReferenceRelation.c	\
	ReferenceIdentity.c	\
	SeqOfReferenceIdentityType.c	\
	ReferenceIdentityType.c	\
	BSICAndCarrier.c	\
	RequestIndex.c	\
	SystemInfoIndex.c	\
	CellIDAndLAC.c	\
	CellID.c	\
	LAC.c	\
	OTD-MeasureInfo.c	\
	SeqOfOTD-MsrElementRest.c	\
	OTD-MsrElementFirst.c	\
	SeqOfOTD-FirstSetMsrs.c	\
	OTD-MsrElementRest.c	\
	SeqOfOTD-MsrsOfOtherSets.c	\
	TOA-MeasurementsOfRef.c	\
	RefQuality.c	\
	NumOfMeasurements.c	\
	StdResolution.c	\
	OTD-FirstSetMsrs.c	\
	OTD-MsrsOfOtherSets.c	\
	OTD-Measurement.c	\
	OTD-MeasurementWithID.c	\
	EOTDQuality.c	\
	NeighborIdentity.c	\
	MultiFrameCarrier.c	\
	OTDValue.c	\
	LocationInfo.c	\
	FixType.c	\
	GPS-MeasureInfo.c	\
	SeqOfGPS-MsrSetElement.c	\
	GPS-MsrSetElement.c	\
	GPSTOW24b.c	\
	SeqOfGPS-MsrElement.c	\
	GPS-MsrElement.c	\
	MpathIndic.c	\
	LocationError.c	\
	LocErrorReason.c	\
	AdditionalAssistanceData.c	\
	GPSAssistanceData.c	\
	GANSSAssistanceData.c	\
	ErrorCodes.c	\
	GPS-AssistData.c	\
	MoreAssDataToBeSent.c	\
	ControlHeader.c	\
	ReferenceTime.c	\
	GPSTime.c	\
	GPSTOW23b.c	\
	GPSWeek.c	\
	GPSTOWAssist.c	\
	GPSTOWAssistElement.c	\
	TLMWord.c	\
	AntiSpoofFlag.c	\
	AlertFlag.c	\
	TLMReservedBits.c	\
	GSMTime.c	\
	FrameNumber.c	\
	TimeSlot.c	\
	BitNumber.c	\
	RefLocation.c	\
	DGPSCorrections.c	\
	SeqOfSatElement.c	\
	SatElement.c	\
	SatelliteID.c	\
	NavigationModel.c	\
	SeqOfNavModelElement.c	\
	NavModelElement.c	\
	SatStatus.c	\
	UncompressedEphemeris.c	\
	EphemerisSubframe1Reserved.c	\
	IonosphericModel.c	\
	UTCModel.c	\
	Almanac.c	\
	SeqOfAlmanacElement.c	\
	AlmanacElement.c	\
	AcquisAssist.c	\
	SeqOfAcquisElement.c	\
	TimeRelation.c	\
	AcquisElement.c	\
	AddionalDopplerFields.c	\
	AddionalAngleFields.c	\
	SeqOf-BadSatelliteSet.c	\
	Rel98-MsrPosition-Req-Extension.c	\
	Rel98-AssistanceData-Extension.c	\
	Rel98-Ext-ExpOTD.c	\
	MsrAssistData-R98-ExpOTD.c	\
	SeqOfMsrAssistBTS-R98-ExpOTD.c	\
	MsrAssistBTS-R98-ExpOTD.c	\
	SystemInfoAssistData-R98-ExpOTD.c	\
	SeqOfSystemInfoAssistBTS-R98-ExpOTD.c	\
	SystemInfoAssistBTS-R98-ExpOTD.c	\
	AssistBTSData-R98-ExpOTD.c	\
	ExpectedOTD.c	\
	ExpOTDUncertainty.c	\
	GPSReferenceTimeUncertainty.c	\
	GPSTimeAssistanceMeasurements.c	\
	Rel-98-MsrPosition-Rsp-Extension.c	\
	OTD-MeasureInfo-R98-Ext.c	\
	OTD-MsrElementFirst-R98-Ext.c	\
	SeqOfOTD-FirstSetMsrs-R98-Ext.c	\
	Rel-5-MsrPosition-Rsp-Extension.c	\
	Extended-reference.c	\
	OTD-MeasureInfo-5-Ext.c	\
	UlPseudoSegInd.c	\
	Rel5-MsrPosition-Req-Extension.c	\
	Rel5-AssistanceData-Extension.c	\
	Rel-5-ProtocolError-Extension.c	\
	Rel7-MsrPosition-Req-Extension.c	\
	GANSSPositioningMethod.c	\
	GANSS-AssistData.c	\
	GANSS-ControlHeader.c	\
	GANSSCommonAssistData.c	\
	SeqOfGANSSGenericAssistDataElement.c	\
	GANSSGenericAssistDataElement.c	\
	GANSSReferenceTime.c	\
	GANSSRefTimeInfo.c	\
	GANSSTOD.c	\
	GANSSTODUncertainty.c	\
	GANSSTOD-GSMTimeAssociation.c	\
	FrameDrift.c	\
	GANSSRefLocation.c	\
	GANSSIonosphericModel.c	\
	GANSSIonosphereModel.c	\
	GANSSIonoStormFlags.c	\
	SeqOfGANSSTimeModel.c	\
	GANSSTimeModelElement.c	\
	TA0.c	\
	TA1.c	\
	TA2.c	\
	GANSSDiffCorrections.c	\
	SeqOfSgnTypeElement.c	\
	SgnTypeElement.c	\
	GANSSSignalID.c	\
	SeqOfDGANSSSgnElement.c	\
	DGANSSSgnElement.c	\
	SVID.c	\
	GANSSNavModel.c	\
	SeqOfGANSSSatelliteElement.c	\
	GANSSSatelliteElement.c	\
	GANSSOrbitModel.c	\
	NavModel-KeplerianSet.c	\
	GANSSClockModel.c	\
	SeqOfStandardClockModelElement.c	\
	StandardClockModelElement.c	\
	GANSSRealTimeIntegrity.c	\
	SeqOfBadSignalElement.c	\
	BadSignalElement.c	\
	GANSSDataBitAssist.c	\
	SeqOf-GANSSDataBits.c	\
	GANSSDataBit.c	\
	GANSSRefMeasurementAssist.c	\
	SeqOfGANSSRefMeasurementElement.c	\
	GANSSRefMeasurementElement.c	\
	AdditionalDopplerFields.c	\
	GANSSAlmanacModel.c	\
	SVIDMASK.c	\
	SeqOfGANSSAlmanacElement.c	\
	GANSSAlmanacElement.c	\
	Almanac-KeplerianSet.c	\
	GANSSUTCModel.c	\
	RequiredResponseTime.c	\
	Rel-7-MsrPosition-Rsp-Extension.c	\
	GANSSLocationInfo.c	\
	PositionData.c	\
	GANSSTODm.c	\
	ReferenceFrame.c	\
	GANSSMeasureInfo.c	\
	SeqOfGANSS-MsrSetElement.c	\
	GANSS-MsrSetElement.c	\
	SeqOfGANSS-SgnTypeElement.c	\
	GANSS-SgnTypeElement.c	\
	SeqOfGANSS-SgnElement.c	\
	GANSS-SgnElement.c	\
	Rel7-AssistanceData-Extension.c	\
	PDU.c	\
	RRLP-Component.c

ASN_MODULE_HEADER=	\
	VelocityEstimate.h	\
	ExtensionContainer.h	\
	Ext-GeographicalInformation.h	\
	MsrPosition-Req.h	\
	MsrPosition-Rsp.h	\
	AssistanceData.h	\
	ProtocolError.h	\
	PositionInstruct.h	\
	MethodType.h	\
	AccuracyOpt.h	\
	Accuracy.h	\
	PositionMethod.h	\
	MeasureResponseTime.h	\
	UseMultipleSets.h	\
	EnvironmentCharacter.h	\
	ReferenceAssistData.h	\
	BTSPosition.h	\
	BCCHCarrier.h	\
	BSIC.h	\
	TimeSlotScheme.h	\
	ModuloTimeSlot.h	\
	MsrAssistData.h	\
	SeqOfMsrAssistBTS.h	\
	MsrAssistBTS.h	\
	MultiFrameOffset.h	\
	RoughRTD.h	\
	SystemInfoAssistData.h	\
	SeqOfSystemInfoAssistBTS.h	\
	SystemInfoAssistBTS.h	\
	AssistBTSData.h	\
	CalcAssistanceBTS.h	\
	ReferenceWGS84.h	\
	FineRTD.h	\
	RelDistance.h	\
	RelativeAlt.h	\
	MultipleSets.h	\
	ReferenceRelation.h	\
	ReferenceIdentity.h	\
	SeqOfReferenceIdentityType.h	\
	ReferenceIdentityType.h	\
	BSICAndCarrier.h	\
	RequestIndex.h	\
	SystemInfoIndex.h	\
	CellIDAndLAC.h	\
	CellID.h	\
	LAC.h	\
	OTD-MeasureInfo.h	\
	SeqOfOTD-MsrElementRest.h	\
	OTD-MsrElementFirst.h	\
	SeqOfOTD-FirstSetMsrs.h	\
	OTD-MsrElementRest.h	\
	SeqOfOTD-MsrsOfOtherSets.h	\
	TOA-MeasurementsOfRef.h	\
	RefQuality.h	\
	NumOfMeasurements.h	\
	StdResolution.h	\
	OTD-FirstSetMsrs.h	\
	OTD-MsrsOfOtherSets.h	\
	OTD-Measurement.h	\
	OTD-MeasurementWithID.h	\
	EOTDQuality.h	\
	NeighborIdentity.h	\
	MultiFrameCarrier.h	\
	OTDValue.h	\
	LocationInfo.h	\
	FixType.h	\
	GPS-MeasureInfo.h	\
	SeqOfGPS-MsrSetElement.h	\
	GPS-MsrSetElement.h	\
	GPSTOW24b.h	\
	SeqOfGPS-MsrElement.h	\
	GPS-MsrElement.h	\
	MpathIndic.h	\
	LocationError.h	\
	LocErrorReason.h	\
	AdditionalAssistanceData.h	\
	GPSAssistanceData.h	\
	GANSSAssistanceData.h	\
	ErrorCodes.h	\
	GPS-AssistData.h	\
	MoreAssDataToBeSent.h	\
	ControlHeader.h	\
	ReferenceTime.h	\
	GPSTime.h	\
	GPSTOW23b.h	\
	GPSWeek.h	\
	GPSTOWAssist.h	\
	GPSTOWAssistElement.h	\
	TLMWord.h	\
	AntiSpoofFlag.h	\
	AlertFlag.h	\
	TLMReservedBits.h	\
	GSMTime.h	\
	FrameNumber.h	\
	TimeSlot.h	\
	BitNumber.h	\
	RefLocation.h	\
	DGPSCorrections.h	\
	SeqOfSatElement.h	\
	SatElement.h	\
	SatelliteID.h	\
	NavigationModel.h	\
	SeqOfNavModelElement.h	\
	NavModelElement.h	\
	SatStatus.h	\
	UncompressedEphemeris.h	\
	EphemerisSubframe1Reserved.h	\
	IonosphericModel.h	\
	UTCModel.h	\
	Almanac.h	\
	SeqOfAlmanacElement.h	\
	AlmanacElement.h	\
	AcquisAssist.h	\
	SeqOfAcquisElement.h	\
	TimeRelation.h	\
	AcquisElement.h	\
	AddionalDopplerFields.h	\
	AddionalAngleFields.h	\
	SeqOf-BadSatelliteSet.h	\
	Rel98-MsrPosition-Req-Extension.h	\
	Rel98-AssistanceData-Extension.h	\
	Rel98-Ext-ExpOTD.h	\
	MsrAssistData-R98-ExpOTD.h	\
	SeqOfMsrAssistBTS-R98-ExpOTD.h	\
	MsrAssistBTS-R98-ExpOTD.h	\
	SystemInfoAssistData-R98-ExpOTD.h	\
	SeqOfSystemInfoAssistBTS-R98-ExpOTD.h	\
	SystemInfoAssistBTS-R98-ExpOTD.h	\
	AssistBTSData-R98-ExpOTD.h	\
	ExpectedOTD.h	\
	ExpOTDUncertainty.h	\
	GPSReferenceTimeUncertainty.h	\
	GPSTimeAssistanceMeasurements.h	\
	Rel-98-MsrPosition-Rsp-Extension.h	\
	OTD-MeasureInfo-R98-Ext.h	\
	OTD-MsrElementFirst-R98-Ext.h	\
	SeqOfOTD-FirstSetMsrs-R98-Ext.h	\
	Rel-5-MsrPosition-Rsp-Extension.h	\
	Extended-reference.h	\
	OTD-MeasureInfo-5-Ext.h	\
	UlPseudoSegInd.h	\
	Rel5-MsrPosition-Req-Extension.h	\
	Rel5-AssistanceData-Extension.h	\
	Rel-5-ProtocolError-Extension.h	\
	Rel7-MsrPosition-Req-Extension.h	\
	GANSSPositioningMethod.h	\
	GANSS-AssistData.h	\
	GANSS-ControlHeader.h	\
	GANSSCommonAssistData.h	\
	SeqOfGANSSGenericAssistDataElement.h	\
	GANSSGenericAssistDataElement.h	\
	GANSSReferenceTime.h	\
	GANSSRefTimeInfo.h	\
	GANSSTOD.h	\
	GANSSTODUncertainty.h	\
	GANSSTOD-GSMTimeAssociation.h	\
	FrameDrift.h	\
	GANSSRefLocation.h	\
	GANSSIonosphericModel.h	\
	GANSSIonosphereModel.h	\
	GANSSIonoStormFlags.h	\
	SeqOfGANSSTimeModel.h	\
	GANSSTimeModelElement.h	\
	TA0.h	\
	TA1.h	\
	TA2.h	\
	GANSSDiffCorrections.h	\
	SeqOfSgnTypeElement.h	\
	SgnTypeElement.h	\
	GANSSSignalID.h	\
	SeqOfDGANSSSgnElement.h	\
	DGANSSSgnElement.h	\
	SVID.h	\
	GANSSNavModel.h	\
	SeqOfGANSSSatelliteElement.h	\
	GANSSSatelliteElement.h	\
	GANSSOrbitModel.h	\
	NavModel-KeplerianSet.h	\
	GANSSClockModel.h	\
	SeqOfStandardClockModelElement.h	\
	StandardClockModelElement.h	\
	GANSSRealTimeIntegrity.h	\
	SeqOfBadSignalElement.h	\
	BadSignalElement.h	\
	GANSSDataBitAssist.h	\
	SeqOf-GANSSDataBits.h	\
	GANSSDataBit.h	\
	GANSSRefMeasurementAssist.h	\
	SeqOfGANSSRefMeasurementElement.h	\
	GANSSRefMeasurementElement.h	\
	AdditionalDopplerFields.h	\
	GANSSAlmanacModel.h	\
	SVIDMASK.h	\
	SeqOfGANSSAlmanacElement.h	\
	GANSSAlmanacElement.h	\
	Almanac-KeplerianSet.h	\
	GANSSUTCModel.h	\
	RequiredResponseTime.h	\
	Rel-7-MsrPosition-Rsp-Extension.h	\
	GANSSLocationInfo.h	\
	PositionData.h	\
	GANSSTODm.h	\
	ReferenceFrame.h	\
	GANSSMeasureInfo.h	\
	SeqOfGANSS-MsrSetElement.h	\
	GANSS-MsrSetElement.h	\
	SeqOfGANSS-SgnTypeElement.h	\
	GANSS-SgnTypeElement.h	\
	SeqOfGANSS-SgnElement.h	\
	GANSS-SgnElement.h	\
	Rel7-AssistanceData-Extension.h	\
	PDU.h	\
	RRLP-Component.h

ASN_MODULE_HEADER+=BOOLEAN.h
ASN_MODULE_SOURCE+=BOOLEAN.c
ASN_MODULE_HEADER+=ENUMERATED.h
ASN_MODULE_SOURCE+=ENUMERATED.c
ASN_MODULE_HEADER+=INTEGER.h
ASN_MODULE_HEADER+=NativeEnumerated.h
ASN_MODULE_SOURCE+=INTEGER.c
ASN_MODULE_HEADER+=NULL.h
ASN_MODULE_SOURCE+=NULL.c
ASN_MODULE_SOURCE+=NativeEnumerated.c
ASN_MODULE_HEADER+=NativeInteger.h
ASN_MODULE_SOURCE+=NativeInteger.c
ASN_MODULE_HEADER+=asn_SEQUENCE_OF.h
ASN_MODULE_SOURCE+=asn_SEQUENCE_OF.c
ASN_MODULE_HEADER+=asn_SET_OF.h
ASN_MODULE_SOURCE+=asn_SET_OF.c
ASN_MODULE_HEADER+=constr_CHOICE.h
ASN_MODULE_SOURCE+=constr_CHOICE.c
ASN_MODULE_HEADER+=constr_SEQUENCE.h
ASN_MODULE_SOURCE+=constr_SEQUENCE.c
ASN_MODULE_HEADER+=constr_SEQUENCE_OF.h
ASN_MODULE_SOURCE+=constr_SEQUENCE_OF.c
ASN_MODULE_HEADER+=constr_SET_OF.h
ASN_MODULE_SOURCE+=constr_SET_OF.c
ASN_MODULE_HEADER+=asn_application.h
ASN_MODULE_HEADER+=asn_system.h
ASN_MODULE_HEADER+=asn_codecs.h
ASN_MODULE_HEADER+=asn_internal.h
ASN_MODULE_HEADER+=OCTET_STRING.h
ASN_MODULE_SOURCE+=OCTET_STRING.c
ASN_MODULE_HEADER+=BIT_STRING.h
ASN_MODULE_SOURCE+=BIT_STRING.c
ASN_MODULE_SOURCE+=asn_codecs_prim.c
ASN_MODULE_HEADER+=asn_codecs_prim.h
ASN_MODULE_HEADER+=ber_tlv_length.h
ASN_MODULE_SOURCE+=ber_tlv_length.c
ASN_MODULE_HEADER+=ber_tlv_tag.h
ASN_MODULE_SOURCE+=ber_tlv_tag.c
ASN_MODULE_HEADER+=ber_decoder.h
ASN_MODULE_SOURCE+=ber_decoder.c
ASN_MODULE_HEADER+=der_encoder.h
ASN_MODULE_SOURCE+=der_encoder.c
ASN_MODULE_HEADER+=constr_TYPE.h
ASN_MODULE_SOURCE+=constr_TYPE.c
ASN_MODULE_HEADER+=constraints.h
ASN_MODULE_SOURCE+=constraints.c
ASN_MODULE_HEADER+=xer_support.h
ASN_MODULE_SOURCE+=xer_support.c
ASN_MODULE_HEADER+=xer_decoder.h
ASN_MODULE_SOURCE+=xer_decoder.c
ASN_MODULE_HEADER+=xer_encoder.h
ASN_MODULE_SOURCE+=xer_encoder.c
ASN_MODULE_HEADER+=per_support.h
ASN_MODULE_SOURCE+=per_support.c
ASN_MODULE_HEADER+=per_decoder.h
ASN_MODULE_SOURCE+=per_decoder.c
ASN_MODULE_HEADER+=per_encoder.h
ASN_MODULE_SOURCE+=per_encoder.c
ASN_MODULE_HEADER+=per_opentype.h
ASN_MODULE_SOURCE+=per_opentype.c

BUILT_SOURCE = asn1.stamp
CLEANFILES = asn1.stamp

EXTRA_DIST = asn1c-files.tgz

ASN_MODULE_OBJS = $(ASN_MODULE_SOURCE:.c=.o)

DIST = Makefile asn1c-files.tgz

ifeq ($(strip $(CONF_PRECOMPILED_ASN)),yes)
ASN1 = asn1-precompiled.stamp
else
ASN1 = asn1.stamp
endif

all: $(ASN1)
	$(MAKE) libs

libs: CFLAGS += $(CONF_ASN_CFLAGS) -I. -fPIC -D_DEFAULT_SOURCE -Wno-format

libs: libasnrrlp.a libasnrrlp.so

libasnrrlp.a: $(ASN_MODULE_OBJS)
	ar rc $@ $(ASN_MODULE_OBJS)

libasnrrlp.so: libasnrrlp.so.1.0
	ln -sf libasnrrlp.so.1 libasnrrlp.so

libasnrrlp.so.1.0: $(ASN_MODULE_OBJS)
	$(CC) -shared -Wl,-soname,libasnrrlp.so.1 -o $@ $^
	ln -sf libasnrrlp.so.1.0 libasnrrlp.so.1

asn1.stamp: $(ASN1_SOURCE)
	asn1c $(CONF_ASN1C_SKELETONS) -gen-PER $(ASN1_SOURCE)
	touch asn1.stamp

asn1-precompiled.stamp:
	tar xzf asn1c-files.tgz
	sed -i -e 's/^int asn_debug_indent;/extern &/' asn_internal.h
	touch asn1-precompiled.stamp

asn1c-files.tgz:
	tar zhcf asn1c-files.tgz $(ASN_MODULE_SOURCE) $(ASN_MODULE_HEADER)

distfiles:
	echo $(addprefix src/asn-rrlp/,$(DIST)) >> $(TOP)/distfiles

clean:
	/bin/rm -f *.o lib*.so* lib*.a *.c *.h *~ *.stamp Makefile.am.sample

.PHONY: clean distfiles asn1c-files asn1c-files.tgz

