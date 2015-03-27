#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/timeb.h>
#include <esl.h>
char guuid[128];
#define disp_msg  printf

 

int check_event_body(const char*eventbody,char*dtmfbuf,int maxdtmf,char* endchar,int *channel_execute)
{	
	char tmp[128];
	unsigned int i,len;
 
	if (eventbody==NULL) return 0;
	len=strlen(eventbody);
	if(len>64) len=64;
	strncpy(tmp,eventbody+strlen("Event-Name: "),len);
	tmp[len]=0;
	for(i=0;i<strlen(tmp);i++) if(tmp[i]=='\n' || tmp[i]=='\r') {tmp[i]=0;break;}

	disp_msg("Event-Name:[%s]", tmp);
	if(strcmp(tmp,"CHANNEL_EXECUTE_COMPLETE")==0)
	{
			if(*channel_execute) return 1;
			disp_msg("CHANNEL_EXECUTE_COMPLETE invalid");
			return 0;
	}
	if(strcmp(tmp,"CHANNEL_EXECUTE")==0) *channel_execute=1;	
	if(strcmp(tmp,"CHANNEL_HANGUP")==0) return -98;
	disp_msg("event_body:%s", eventbody);
	//if(strcmp(tmp,"CHANNEL_PROGRESS")==0)
	 
	if(_strnicmp(eventbody,"Event-Name: DTMF",strlen("Event-Name: DTMF"))==0)
	{							
		char*p;
		
		if(p=strstr(eventbody,"DTMF-Digit: "))
		{
			strcpy(tmp,p+strlen("DTMF-Digit: "));
			for(i=0;i<strlen(tmp);i++)if(tmp[i]=='\n' || tmp[i]=='\r') {tmp[i]=0;break;}
			if(strcmp(tmp,"%23")==0) strcpy(tmp,"#");
			disp_msg("dtmf:[%s]", tmp);
			if(dtmfbuf && strlen(dtmfbuf)<64) strcat(dtmfbuf,tmp);
			if(strlen(dtmfbuf)>=maxdtmf) return 2;
			len=strlen(endchar);		
			//֧�����3����������
			if(len>0) if(tmp[0]==endchar[0]) return 3;
			if(len>1) if(tmp[0]==endchar[1]) return 3;
			if(len>2) if(tmp[0]==endchar[2]) return 3;
		}
	}
	return 0;
}


int check_acm_body(const char*eventbody,char*uuid)
{	
	char tmp[4096];
	unsigned int i,len;
 	char*p;
	if (eventbody==NULL) return 0;
	len=strlen(eventbody);
	if(len>64) len=64;
	strncpy(tmp,eventbody+strlen("Event-Name: "),len);
	tmp[len]=0;
	for(i=0;i<strlen(tmp);i++) if(tmp[i]=='\n' || tmp[i]=='\r') {tmp[i]=0;break;}

	disp_msg("Event-Name:[%s]", tmp);
	 
//	disp_msg("event_body:%s", eventbody);
	if(strcmp(tmp,"CHANNEL_PROGRESS")!=0)
	{
		return 0;
	}
	 



	if(p=strstr(eventbody,"Unique-ID: "))
	{
		strcpy(tmp,p+strlen("Unique-ID: "));
		for(i=0;i<strlen(tmp);i++)if(tmp[i]=='\n' || tmp[i]=='\r') {tmp[i]=0;break;}
		 
		disp_msg("acm UUID:[%s]", tmp);
		strcpy(uuid,tmp);			 
	}

	return 1;
}
int check_event(esl_handle_t *handle,int timer)
{
	int done = 0,c=0;
	esl_status_t status;
	time_t exp = 0;
	char dtmf[128];
	int res=0;
	int  channel_execute=0;
	dtmf[0]=0;
	while((status = esl_recv_timed(handle, 1000)) != ESL_FAIL) 
	{	
		c++;
		disp_msg("Waiting 1 seconds events.\n");
		if(timer>0 && c>=timer){res=100;break;}
	 
		if (status == ESL_SUCCESS) 
		{
			const char *type = esl_event_get_header(handle->last_event, "content-type");
			
			if (type)
			{
				if(strcasecmp(type, "text/disconnect-notice")==0) 
				{
					const char *dispo = esl_event_get_header(handle->last_event, "content-disposition");
					disp_msg("Got a disconnection notice dispostion: [%s]", dispo ? dispo : "");
					if (dispo && strcmp(dispo, "linger")==0) 
					{
						res=-99;
						break;					 
					}
				}
				if(strcasecmp(type, "text/event-plain")==0) 
				{		
					const char *eventbody=esl_event_get_body(handle->last_event);
					if((res=check_event_body(eventbody,dtmf,1,"#",&channel_execute)))
					{
						disp_msg("check_event_body res=%d.",res);
						if(res<0)	break;
					}
				}

			}
		} 	
	}
	disp_msg("check_event res=%d",res);
	return res;
}

int check_last_event(esl_handle_t *handle,int timer)
{
	int done = 0,c=0;
	esl_status_t status;
	time_t exp = 0;
	char dtmf[128];
	int res=0;
	int  channel_execute=0;

	dtmf[0]=0;
	while((status = esl_recv_timed(handle, 1000)) != ESL_FAIL) 
	{	
		c++;
	//	disp_msg("Waiting 1 seconds events.\n");
		if(timer>0 && c>=timer){res=99;break;}
		
		if (done) 
		{
			if (time(NULL) >= exp) {res=-99;	break;	}		 
			continue;
		} 
		if (status == ESL_SUCCESS) 
		{
		
			const char *type = esl_event_get_header(handle->last_event, "content-type");
			 

			if (type)
			{
				if(strcasecmp(type, "text/disconnect-notice")==0) 
				{
					const char *dispo = esl_event_get_header(handle->last_event, "content-disposition");
					disp_msg("Got a disconnection notice dispostion: [%s]", dispo ? dispo : "");
					if (dispo && strcmp(dispo, "linger")==0) 
					{
						done = 1;
						exp = time(NULL) + 5;
					}
				}

				if(strcasecmp(type, "text/event-plain")==0) 
				{		
					const char *eventbody=esl_event_get_body(handle->last_event);
					if((res=check_event_body(eventbody,dtmf,1,"#",&channel_execute)))
					{
						disp_msg("check_last_event_body res=%d.",res);
					}
				}

			}
		} 	
	}
	disp_msg("check_last_event res=%d.",res);
	return res;
}

int check_acm_event(esl_handle_t *handle,int timer,char* uuid)
{
	int done = 0,c=0;
	esl_status_t status;
	time_t exp = 0;
 	int res=0;

	uuid[0]=0;
	while((status = esl_recv_timed(handle, 1000)) != ESL_FAIL) 
	{	
		c++;
	//	disp_msg("Waiting 1 seconds events.\n");
		if(timer>0 && c>=timer){res=99;break;}
		
		if (done) 
		{
			if (time(NULL) >= exp) {res=-99;	break;	}		 
			continue;
		} 
		if (status == ESL_SUCCESS) 
		{
		
			const char *type = esl_event_get_header(handle->last_event, "content-type");
			 

			if (type)
			{
				if(strcasecmp(type, "text/disconnect-notice")==0) 
				{
					const char *dispo = esl_event_get_header(handle->last_event, "content-disposition");
					disp_msg("Got a disconnection notice dispostion: [%s]", dispo ? dispo : "");
					if (dispo && strcmp(dispo, "linger")==0) 
					{
						done = 1;
						exp = time(NULL) + 5;
					}
				}

				if(strcasecmp(type, "text/event-plain")==0) 
				{		
					const char *eventbody=esl_event_get_body(handle->last_event);
					if((res=check_acm_body(eventbody,uuid)))
					{
						disp_msg("check_acm_body res=%d.",res);
						break;
					}
				}
			}
		} 	
	}
	disp_msg("check_acm_event res=%d.",res);
	return res;
}

//����֮���ȡ������麯��
//����: <0 ��ʾ�Է��һ���=100 ��ʾ�������ʱ������������� =101 ��ʾ����������ļ��ʱ�����������������,=3��ʾ ������������,����"#" ���㣬=2��ʾ ��󰴼������������� ����
//����:handle:�Ựhandle
//filename:�����ļ����ƣ�����ļ��Էֺ�";"����,�ļ����ƿ��Դ�.wav,��չ��,����û��,Ĭ����.pcm��չ��.��ָ��·��,����û��,Ĭ�������������./data/systemĿ¼��
//enddtmf:������������,����"#"��ʾ��#�Ž�������,""��ʾû�н�����������//֧�����3���������� ���� EndDtmf="*0#" ��ʾ�� 0��* ����#�����Խ���
//MaxDtmf:��󰴼�������������,0��ʾû�а���������������
//MaxTimer:�������ʱ���������,��λ��,0��ʾû�����ʱ���������
//TwoDtmfTimer:����������ļ��ʱ���������,��λ��,0��ʾû������������ļ��ʱ���������
//outdtmf:�յ����û��İ���(�������),������������������,����"#"
//����˵��:����ֻ�в���,����ȡ���� ���ã�MaxDtmf=0
int check_play_dtmf_event(esl_handle_t *handle,char*enddtmf,int MaxDtmf,int MaxTimer,int TwoDtmfTimer,char*outdtmf)
{
	int done = 0,c=0,twodtmfc=0;
	esl_status_t status;
	time_t exp = 0;
	char dtmf[128];
	int res=0,press_dtmf;
	int  channel_execute=0;

	press_dtmf=0;
	dtmf[0]=0;
	while((status = esl_recv_timed(handle, 1000)) != ESL_FAIL) 
	{
		if(press_dtmf)
		{
			twodtmfc++;	
			c++;
		}
		//disp_msg("Waiting 1 seconds events.\n");
		if(MaxTimer>0 && c>=MaxTimer){disp_msg("Waiting alldtmf %d seconds timout.",c); res=100;break;}
		if(TwoDtmfTimer>0 && twodtmfc>0 && twodtmfc>=TwoDtmfTimer){disp_msg("Waiting twodtmf %d seconds timout.",c); res=101;break;}
		if (status == ESL_SUCCESS) 
		{
			const char *type = esl_event_get_header(handle->last_event, "content-type");
			if (type)
			{
				if(strcasecmp(type, "text/disconnect-notice")==0) 
				{
					const char *dispo = esl_event_get_header(handle->last_event, "content-disposition");
					disp_msg("Got a disconnection notice dispostion: [%s]", dispo ? dispo : "");
					if (dispo && strcmp(dispo, "linger")==0) 
					{
						res=-99;
						break;					 
					}
				}
				if(strcasecmp(type, "text/event-plain")==0) 
				{		
					const char *eventbody=esl_event_get_body(handle->last_event);
					int oldlen=strlen(outdtmf);
					if(res=check_event_body(eventbody,outdtmf,MaxDtmf,enddtmf,&channel_execute))
					{
						disp_msg("check_play_dtmf_event res=%d.",res);						 
						if(res==1)//play ���� ��ʼ�Ȱ���
						{
							press_dtmf=1;
							if(MaxDtmf==0) break;
						}
						else
							break;
					}			
					if(oldlen==1) press_dtmf=1;
					if(strlen(outdtmf)>oldlen)	twodtmfc=0;
				}
			}
		} 	
	}
	return res;
}
//����ȡ����
//����: <0 ��ʾ�Է��һ���=100 ��ʾ�������ʱ������������� =101 ��ʾ����������ļ��ʱ�����������������,=3��ʾ ������������,����"#" ���㣬=2��ʾ ��󰴼������������� ����
//����:handle:�Ựhandle
//filename:�����ļ����ƣ�����ļ��Էֺ�";"����,�ļ����ƿ��Դ�.wav,��չ��,����û��,Ĭ����.pcm��չ��.��ָ��·��,����û��,Ĭ�������������./data/systemĿ¼��
//EndDtmf:������������,����"#"��ʾ��#�Ž�������,""��ʾû�н�����������//֧�����3���������� ���� EndDtmf="*0#" ��ʾ�� 0��* ����#�����Խ���
//MaxDtmf:��󰴼�������������,0��ʾû�а���������������
//MaxTimer:�������ʱ���������,��λ��,0��ʾû�����ʱ���������
//TwoDtmfTimer:����������ļ��ʱ���������,��λ��,0��ʾû������������ļ��ʱ���������
//dtmf:�յ����û��İ���(�������),������������������,����"#"
//˵��:����ֻ�в���,����ȡ���� ���ã�MaxDtmf=0
#define  playdir  "d:/data/system"
int play_get_dtmf(esl_handle_t *handle,char*filename0,char*EndDtmf,int MaxDtmf,int MaxTimer,int TwoDtmfTimer,char*outdtmf)
{
	int res=0;
	char cmd_tmp[1024],enddtmf[128],outdtmfbuff[128],filename[128];
	if(EndDtmf==NULL || EndDtmf[0]==0) 
		strcpy(enddtmf,"q");
	else
		strcpy(enddtmf,EndDtmf);
	if(outdtmf) outdtmf[0]=0;
	memset(outdtmfbuff,0,sizeof(outdtmfbuff));
	
	sprintf(filename,"%s/%s",playdir,filename0);			
	if(_access(filename,0)==-1)
		sprintf(filename,"%s/default.alaw",playdir); 

	//<min> <max> <tries> <timeout ms> <terminators> <file> 
	sprintf(cmd_tmp,"1 1 1 10 a %s",filename);//������play_get_dtmf ��������İ�������������Ч��ivr check_dtmf_event �����Լ��������ж�
	disp_msg("play_get_dtmf %s",filename);
	esl_execute(handle, "play_and_get_digits",cmd_tmp, NULL);

	res=check_play_dtmf_event(handle,enddtmf,MaxDtmf,MaxTimer,TwoDtmfTimer,outdtmfbuff);
	if(outdtmf) strcpy(outdtmf,outdtmfbuff);	
	disp_msg("play_get_dtmf %s end,dtmf=[%s]",filename,outdtmfbuff);
	return res;
}
//¼��֮���ȡ������麯��
//����: <0 ��ʾ�Է��һ���=100 ��ʾ�������ʱ������������� =101 ��ʾ����������ļ��ʱ�����������������,=3��ʾ ������������,����"#" ���㣬=2��ʾ ��󰴼������������� ����
//����:handle:�Ựhandle
//filename:�����ļ����ƣ�����ļ��Էֺ�";"����,�ļ����ƿ��Դ�.wav,��չ��,����û��,Ĭ����.pcm��չ��.��ָ��·��,����û��,Ĭ�������������./data/systemĿ¼��
//enddtmf:������������,����"#"��ʾ��#�Ž�������,""��ʾû�н�����������//֧�����3���������� ���� EndDtmf="*0#" ��ʾ�� 0��* ����#�����Խ���
//MaxDtmf:��󰴼�������������,0��ʾû�а���������������
//MaxTimer:�������ʱ���������,��λ��,0��ʾû�����ʱ���������
//TwoDtmfTimer:����������ļ��ʱ���������,��λ��,0��ʾû������������ļ��ʱ���������
//outdtmf:�յ����û��İ���(�������),������������������,����"#"
//����˵��:����ֻ�в���,����ȡ���� ���ã�MaxDtmf=0

int check_record_dtmf_event(esl_handle_t *handle,char*enddtmf,int MaxDtmf,int MaxTimer,int TwoDtmfTimer,char*outdtmf)
{
	int done = 0,c=0,twodtmfc=0;
	esl_status_t status;
	time_t exp = 0;
	char dtmf[128];
	int res=0,press_dtmf;
	int  channel_execute=0;

	press_dtmf=1;
	dtmf[0]=0;
	while((status = esl_recv_timed(handle, 1000)) != ESL_FAIL) 
	{
		if(press_dtmf)
		{
			twodtmfc++;	
			c++;
		}
		if(MaxTimer>0 && c>=MaxTimer){disp_msg("Waiting alldtmf %d seconds timout.",c); res=100;break;}
		if(TwoDtmfTimer>0 && twodtmfc>0 && twodtmfc>=TwoDtmfTimer){disp_msg("Waiting twodtmf %d seconds timout.",c); res=101;break;}
		if (status == ESL_SUCCESS) 
		{
			const char *type = esl_event_get_header(handle->last_event, "content-type");
			if (type)
			{
				if(strcasecmp(type, "text/disconnect-notice")==0) 
				{
					const char *dispo = esl_event_get_header(handle->last_event, "content-disposition");
					disp_msg("Got a disconnection notice dispostion: [%s]", dispo ? dispo : "");
					if (dispo && strcmp(dispo, "linger")==0) 
					{
						res=-99;
						break;					 
					}
				}
				if(strcasecmp(type, "text/event-plain")==0) 
				{		
					const char *eventbody=esl_event_get_body(handle->last_event);
					int oldlen=strlen(outdtmf);
					if((res=check_event_body(eventbody,outdtmf,MaxDtmf,enddtmf,&channel_execute)))
					{
						break;
					}			
					if(oldlen==1) press_dtmf=1;
					if(strlen(outdtmf)>oldlen)	twodtmfc=0;
				}
			}
		} 	
	}
	return res;
}
//¼��ȡ��������
//����: <0 ��ʾ�Է��һ���=100 ��ʾ�������ʱ������������� =101 ��ʾ����������ļ��ʱ�����������������,=3��ʾ ������������,����"#" ���㣬=2��ʾ ��󰴼������������� ����
//����:handle:�Ựhandle
//uuid�� �Ự��id
//filename:�����ļ����ƣ�����ļ��Էֺ�";"����,�ļ����ƿ��Դ�.wav,��չ��,����û��,Ĭ����.pcm��չ��.��ָ��·��,����û��,Ĭ�������������./data/systemĿ¼��
//EndDtmf:������������,����"#"��ʾ��#�Ž�������,""��ʾû�н�����������//֧�����3���������� ���� EndDtmf="*0#" ��ʾ�� 0��* ����#�����Խ���
//MaxDtmf:��󰴼�������������,0��ʾû�а���������������
//MaxTimer:�������ʱ���������,��λ��,0��ʾû�����ʱ���������
//TwoDtmfTimer:����������ļ��ʱ���������,��λ��,0��ʾû������������ļ��ʱ���������
//outdtmf:�յ����û��İ���(�������),������������������,����"#"
int record_get_dtmf(esl_handle_t *handle,char*uuid,char*filename,char*EndDtmf,int MaxDtmf,int MaxTimer,int TwoDtmfTimer,char*outdtmf)
{
	int res;
	char cmd_tmp[1024],enddtmf[128],outdtmfbuff[128];
	if(EndDtmf==NULL || EndDtmf[0]==0) 
		strcpy(enddtmf,"q");
	else
		strcpy(enddtmf,EndDtmf);
	if(outdtmf) outdtmf[0]=0;
	
	disp_msg("record_get_dtmf:%s",filename);
	memset(outdtmfbuff,0,sizeof(outdtmfbuff));
	sprintf(cmd_tmp,"api uuid_record %s start %s %d",uuid,filename,MaxTimer*2);//MaxTimer*2��������Ϊ�˱�֤uuid_record ��������Ч������ͨ���Լ���ivr check_record_dtmf_event���������������¼�������ж�
	esl_send_recv_timed(handle, cmd_tmp,1000); 	
	res=check_record_dtmf_event(handle,enddtmf,MaxDtmf,MaxTimer,TwoDtmfTimer,outdtmfbuff);
	if(outdtmf) strcpy(outdtmf,outdtmfbuff);
	disp_msg("record_get_dtmf:%s,end,dtmf=[%s]",filename,outdtmfbuff);
	sprintf(cmd_tmp,"api uuid_record %s stop all",uuid);
	disp_msg("record_get_dtmf:%s stop",filename);
	esl_send_recv_timed(handle, cmd_tmp,1000);
	disp_msg("record_get_dtmf:%s stop end",filename);

	return res;
}

static void mycallback(esl_socket_t server_sock, esl_socket_t client_sock, struct sockaddr_in *addr)
{
	char  uuid[128];
	char cmd_tmp[128],dtmf[128];
	char recordfilename[128];
	
	esl_handle_t handle = {{0}};

	esl_attach_handle(&handle, client_sock, addr);

	//disp_msg("Connected! %d", handle.sock);

	esl_filter(&handle, "unique-id", esl_event_get_header(handle.info_event, "caller-unique-id"));

	strcpy(uuid,esl_event_get_header(handle.info_event, "caller-unique-id"));

	disp_msg("handle.sock=%d,UUID=%s",handle.sock,uuid);

	esl_events(&handle, ESL_EVENT_TYPE_PLAIN, "SESSION_HEARTBEAT CHANNEL_ANSWER CHANNEL_ORIGINATE CHANNEL_PROGRESS CHANNEL_HANGUP "
			   "CHANNEL_BRIDGE CHANNEL_UNBRIDGE CHANNEL_OUTGOING CHANNEL_EXECUTE CHANNEL_EXECUTE_COMPLETE DTMF CUSTOM conference::maintenance");

	//This will send a command and place its response event on handle->last_sr_event and handle->last_sr_reply
	esl_send_recv(&handle, "linger");//Tells FreeSWITCH not to close the socket connect when a channel hangs up. Instead, it keeps the socket connection open until the last event related to the channel has been received by the socket client. 
	
	esl_execute(&handle, "answer", NULL, NULL);
	if(check_event(&handle,2)<0) goto END;
	
	if(play_get_dtmf(&handle,"hello.alaw","#",0,0,0,dtmf)<0) goto END;	//hello.alaw:"��ӭ�µ��ҹ�˾�����ǹ�˾��ת���ṩ400����˾"	
	while(1)
	{
		if(play_get_dtmf(&handle,"menu.alaw","*0#",5,20,0,dtmf)<0) goto END;//menu.alaw:"������ֻ����룬��#��ȷ�ϣ������밴�Ǻţ��˹������밴0,�μӻ����밴#��"		
		if(dtmf[0]!=0) 
		{
			break;
		}
	}
	switch(dtmf[0])
	{
	case '*'://����
		{
			if(play_get_dtmf(&handle,"startrecord.alaw","#",0,0,0,dtmf)<0)   goto END;	//startrecord.alaw:���������ε�һ��֮��ʼ¼���������������¼��,��.....
			sprintf(recordfilename,"z:/%s.alaw",uuid);//¼�Ƶ� z:/Ŀ¼�� .alaw ��չ�� ¼��Ϊ 8K16bit ��alaw ��ʽ������.wav��չ��¼��Ϊ 8K16bit ������pcm��ʽ����
			if(record_get_dtmf(&handle,uuid,recordfilename,"#",1,30,0,dtmf)<0) goto END;	
			if(play_get_dtmf(&handle,recordfilename,"#",0,0,0,dtmf)<0)   goto END;	
			if(play_get_dtmf(&handle,"bye.alaw","#",0,0,0,dtmf)<0)   goto END;	//bye.alaw:"ллʹ�ã��ټ�"
			break;
		}
	case '0'://�˹�����
		{
			esl_execute(&handle, "bridge", "user/1000@${domain_name}", NULL); 
			/* uuid_transfer
				Transfers an existing call to a specific extension within a <dialplan> and <context>. Dialplan may be "xml" or "directory".
				Usage:
				uuid_transfer <uuid> [-bleg|-both] <dest-exten> [<dialplan>] [<context>]
				The optional first argument will allow you to transfer both parties (-both) or only the party to whom <uuid> is talking.(-bleg)
				NOTE: if the call has been bridged, and you want to transfer either sides of the call, then you will need to 
				use <action application="set" data="hangup_after_bridge=false"/> (or the API equivalent). 
				If it's not set, transfer doesn't really work as you'd expect, and leaves calls in limbo. */
			if(check_event(&handle,0)<0) goto END;
			break;
		}

	case '#'://�μӻ���
		{
			esl_execute(&handle, "conference", "3000@default", NULL);	
			if(check_event(&handle,0)<0) goto END;
			break;
		}

	default: 
		{
			strtok(dtmf,"#");//ȥ��#�ż�
			sprintf(cmd_tmp,"user/%s@${domain_name}",dtmf);////${domain_name}=192.168.1.236
			esl_execute(&handle, "bridge",cmd_tmp , NULL);
			if(check_event(&handle,0)<0) goto END;
			break;
		}
	}
	disp_msg("ivr hangup.....\n");
	sprintf(cmd_tmp,"api uuid_kill %s",uuid);
	esl_send_recv_timed(&handle, cmd_tmp,1000);

END:	
	disp_msg("check_last_event start.....\n");
	check_last_event(&handle,10);
	disp_msg("Disconnected!");
	esl_disconnect(&handle);
}

 
int	CallOutThread(void* arg)
{
	char uuid[128],tmp[1024];
	esl_handle_t handle = {{0}};
	int res;
	res=esl_connect(&handle, "127.0.0.1", 8021, NULL, "ClueCon");//
	esl_send_recv(&handle, "api create_uuid\n\n");
 	if (handle.last_sr_event && handle.last_sr_event->body) 
	{
		printf("uuid:[%s]\n", handle.last_sr_event->body);
		strcpy(uuid,handle.last_sr_event->body);
		//strcpy(uuid,(handle.last_sr_event->body)+strlen("+OK Job-UUID: "));
	} 
	else 
	{
		printf("[%s] last_sr_reply\n", handle.last_sr_reply);
	}
	getchar();
	sprintf(tmp,"bgapi originate {origination_uuid=%s,originate_timeout=30}sofia/internal/1005%c192.168.1.102 &park()\n\n",uuid,'%');//origination_uuid=
	disp_msg("cmd=[%s]",tmp);
	//esl_send_recv(&handle, "bgapi originate {originate_timeout=30}sofia/internal/1005%192.168.1.102 &park()\n\n");
	esl_send_recv(&handle,tmp);// "bgapi originate {originate_timeout=30}sofia/internal/1005%192.168.1.102 &park()\n\n");
//	uuid[0]=0;
	if (handle.last_sr_event && handle.last_sr_event->body) 
	{
		printf("[%s]\n", handle.last_sr_event->body);
	//	strcpy(uuid,(handle.last_sr_event->body)+strlen("+OK Job-UUID: "));
	} 
	else 
	{
		printf("[%s] last_sr_reply\n", handle.last_sr_reply);
	}
//	esl_events(&handle, ESL_EVENT_TYPE_PLAIN, "CHANNEL_PROGRESS");
 
	esl_send_recv(&handle, "linger");//Tells FreeSWITCH not to close the socket connect when a channel hangs up. Instead, it keeps the socket connection open until the last event related to the channel has been received by the socket client. 
	//res=check_acm_event(&handle,100,uuid);
//	if(res==1)
	//{
			esl_filter(&handle, "unique-id", uuid);
				esl_events(&handle, ESL_EVENT_TYPE_PLAIN, "SESSION_HEARTBEAT CHANNEL_ANSWER CHANNEL_ORIGINATE CHANNEL_PROGRESS CHANNEL_HANGUP "
			   "CHANNEL_BRIDGE CHANNEL_UNBRIDGE CHANNEL_OUTGOING CHANNEL_EXECUTE CHANNEL_EXECUTE_COMPLETE DTMF CUSTOM conference::maintenance");
	//This will send a command and place its response event on handle->last_sr_event and handle->last_sr_reply
	//}
	esl_send_recv(&handle, "linger");
	check_last_event(&handle,30);
	disp_msg("Disconnected!");
	disp_msg("esl_disconnect ok.\n ...");
	esl_disconnect(&handle);
	getchar();
	return 0;
} 
int main(void)
{
	WSADATA Data;
	if( WSAStartup(MAKEWORD(2, 1), &Data) != 0)
	{
		return 0;
	}	
	esl_global_set_default_logger(6);
	
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CallOutThread,(LPVOID)(0),0, NULL);
		
	disp_msg("System Start ok.\nstart mycallback and  wait callin....");

	esl_listen_threaded("127.0.0.1", 8084, mycallback, 100000);


}