/*
	PPPoE Intermediate agent defenitons
	Mike Ireton ( mike-ilc@TieDyeNetworks.Com )
*/

#define	TAG_TR101_CIRCUIT_ID				0x01
#define	TAG_TR101_REMOTE_ID				0x02
#define	TAG_TR101_DATARATE_UPSTREAM			0x81
#define	TAG_TR101_DATARATE_DOWNSTREAM			0x82
#define	TAG_TR101_MIN_DATARATE_UPSTREAM			0x83
#define	TAG_TR101_MIN_DATARATE_DOWNSTREAM		0x84
#define	TAG_TR101_ATTAIN_DATARATE_UPSTREAM		0x85
#define	TAG_TR101_ATTAIN_DATARATE_DOWNSTREAM		0x86
#define	TAG_TR101_MAX_DATARATE_UPSTREAM			0x87
#define	TAG_TR101_MAX_DATARATE_DOWNSTREAM		0x88
#define	TAG_TR101_LOWPOWER_MIN_DATARATE_UPSTREAM	0x89
#define	TAG_TR101_LOWPOWER_MIN_DATARATE_DOWNSTREAM	0x8A
#define	TAG_TR101_MAX_INTERLEAVEDELAY_UPSTREAM		0x8B
#define	TAG_TR101_ACTUAL_INTERLEAVEDELAY_UPSTREAM	0x8C
#define	TAG_TR101_MAX_INTERLEAVEDELAY_DOWNSTREAM	0x8D
#define	TAG_TR101_ACTUAL_INTERLEAVEDELAY_DOWNSTREAM	0x8E
#define	TAG_TR101_ACCESS_LOOP_ENCAPSULATION		0x90

typedef struct Tr101PiaStruct {
	char 	CircuitId[64];
	char 	RemoteId[64];
	long int	DataRateUpstream;
	long int	DataRateDownstream;
	long int	MinDataRateUpstream;
	long int	MinDataRateDownstream;
	long int	AttainDataRateUpstream;
	long int	AttainDataRateDownstream;
	long int	MaxDataRateUpstream;
	long int	MaxDataRateDownstream;
	long int	LowPowerMinDataRateUpstream;
	long int	LowPowerMinDataRateDownstream;
	long int	MaxInterleaveDelayUpstream;
	long int	ActualInterleaveDelayUpstream;
	long int	MaxInterleaveDelayDownstream;
	long int	ActualInterleaveDelayDownstream;
	unsigned char	AccessLoopEncapsulation[3];
} Tr101PiaTags;

typedef struct Tr101PiaVendorOptionStruct {
	unsigned char	Option;
	unsigned char	Length;
	unsigned char	Data;
} Tr101PiaVendorOption;


void	initTr101Pia(Tr101PiaTags *pia);
void 	printTr101Pia(Tr101PiaTags *pia);
int 	processTr101Pia(Tr101PiaTags *pia,void *data, int len);

