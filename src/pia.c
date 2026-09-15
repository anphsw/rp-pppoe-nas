/*
	PPPoE Intermediate Agent support for RP-PPPOE

	Based on ADSL forum Technical Report 101

	Mike Ireton ( mike-ilc@TieDyeNetworks.Com )
	"The Insane Laughing Clown of Wireless Broadband"
	07/2010
*/

#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <arpa/inet.h>
#include "pia.h"

void	initTr101Pia(Tr101PiaTags *pia)
{
	memset(pia->CircuitId,0,sizeof(pia->CircuitId));
	memset(pia->RemoteId,0,sizeof(pia->RemoteId));
	pia->DataRateUpstream=-1;
	pia->DataRateDownstream=-1;
	pia->MinDataRateUpstream=-1;
	pia->MinDataRateDownstream=-1;
	pia->AttainDataRateUpstream=-1;
	pia->AttainDataRateDownstream=-1;
	pia->MaxDataRateUpstream=-1;
	pia->MaxDataRateDownstream=-1;
	pia->LowPowerMinDataRateUpstream=-1;
	pia->LowPowerMinDataRateDownstream=-1;
	pia->MaxInterleaveDelayUpstream=-1;
	pia->ActualInterleaveDelayUpstream=-1;
	pia->MaxInterleaveDelayDownstream=-1;
	pia->ActualInterleaveDelayDownstream=-1;
	memset(pia->AccessLoopEncapsulation,0,sizeof(pia->AccessLoopEncapsulation));
}

int processTr101Pia(Tr101PiaTags *pia,void *data, int len)
{
	int			processedLen, tagsize;
	long int		value;

	Tr101PiaVendorOption	*opts;

	initTr101Pia(pia);

	opts=data;
	processedLen=2;
/*
	Step thru the data packet picking out all sub tags
*/
while(processedLen < len )	{

	memcpy(&value, &opts->Data,4);
	value=ntohl(value);

/* optimize the big case() below */

	tagsize=6;
	switch(opts->Option) {

	case(TAG_TR101_CIRCUIT_ID):
	{
		if(opts->Length >63) { syslog(LOG_WARNING,"tr101: Invalid CircuitId length (%d)\n",opts->Length); return -1; }
		strncpy(pia->CircuitId,(void *)&opts->Data,opts->Length);
		tagsize=opts->Length+2;
		break;
	}
	case(TAG_TR101_REMOTE_ID):
	{
		if(opts->Length >63) { syslog(LOG_WARNING,"tr101: Invalid RemoteId length (%d)\n",opts->Length); return -1; }
		strncpy(pia->RemoteId,(void *)&opts->Data,opts->Length);
		tagsize=opts->Length+2;
		break;
	}
	case(TAG_TR101_DATARATE_UPSTREAM):
				pia->DataRateUpstream=value;
				break;
	case(TAG_TR101_DATARATE_DOWNSTREAM):
				pia->DataRateDownstream=value;
				break;
	case(TAG_TR101_MIN_DATARATE_UPSTREAM):
				pia->MinDataRateUpstream=value;
				break;
	case(TAG_TR101_MIN_DATARATE_DOWNSTREAM):
				pia->MinDataRateDownstream=value;
				break;
	case(TAG_TR101_ATTAIN_DATARATE_UPSTREAM):
				pia->AttainDataRateUpstream=value;
				break;
	case(TAG_TR101_ATTAIN_DATARATE_DOWNSTREAM):
				pia->AttainDataRateDownstream=value;
				break;
	case(TAG_TR101_MAX_DATARATE_UPSTREAM):
				pia->MaxDataRateUpstream=value;
				break;
	case(TAG_TR101_MAX_DATARATE_DOWNSTREAM):
				pia->MaxDataRateDownstream=value;
				break;
	case(TAG_TR101_LOWPOWER_MIN_DATARATE_UPSTREAM):
				pia->LowPowerMinDataRateUpstream=value;
				break;
	case(TAG_TR101_LOWPOWER_MIN_DATARATE_DOWNSTREAM):
				pia->LowPowerMinDataRateDownstream=value;
				break;
	case(TAG_TR101_MAX_INTERLEAVEDELAY_UPSTREAM):
				pia->MaxInterleaveDelayUpstream=value;
				break;
	case(TAG_TR101_ACTUAL_INTERLEAVEDELAY_UPSTREAM):
				pia->ActualInterleaveDelayUpstream=value;
				break;
	case(TAG_TR101_MAX_INTERLEAVEDELAY_DOWNSTREAM):
				pia->MaxInterleaveDelayDownstream=value;
				break;
	case(TAG_TR101_ACTUAL_INTERLEAVEDELAY_DOWNSTREAM):
				pia->ActualInterleaveDelayDownstream=value;
				break;
	case(TAG_TR101_ACCESS_LOOP_ENCAPSULATION):
				memcpy(pia->AccessLoopEncapsulation,&opts->Length,3);
				tagsize=3;
				break;
	default:
		syslog(LOG_WARNING,"processing pia tags: unknown option: %x\n",opts->Option);
		return -1;
	break;
	}
	processedLen+=tagsize;
	opts = (Tr101PiaVendorOption *)((char *) opts + tagsize);

	}
	return 0;
}
