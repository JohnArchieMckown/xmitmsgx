/*
 *
 *        Name: xmitmsgx.h, "transmit message" for POSIX
 *              read and emit enumerated messages from the repository
 *      Author: Rick Troth, rogue programmer
 *        Date: 2014-May-01 (Thu)
 *              2017-Nov-23 (Thu) Thanksgiving 2017
 *
 */

#ifndef _XMITMSG_H
#define _XMITMSG_H

/*               _DEBUG             SYSLOG 7 */
#define  MSGLEVEL_INFO      'I'  /* SYSLOG 6 */
#define  MSGLEVEL_REPLY     'R'  /* SYSLOG 5 NOTICE */
#define  MSGLEVEL_WARNING   'W'  /* SYSLOG 4 */
#define  MSGLEVEL_ERROR     'E'  /* SYSLOG 3 */
#define  MSGLEVEL_SEVERE    'S'  /* SYSLOG 2 CRIT */
#define  MSGLEVEL_TERMINAL  'T'  /* SYSLOG 1 ALERT */
/*               _EMERG             SYSLOG 0 */

/* the following are used by derivative functions, not by msgmake() itself */
#define  MSGFLAG_SYSLOG   0x01
#define  MSGFLAG_NOCODE   0x02
#define  MSGFLAG_NOPRINT  0x04


extern int msgopen(const char*,int,struct MSGSTRUCT*);
/* filename, flags, optional MSGSTRUCT */
/* specify a syslog ident via applid in optional MSGSTRUCT */
/* specify a syslog facility via optional MSGSTRUCT */
/* on CMS it might do a 'SET LANG' to load the messages file */

/* this is the heart of the utility */
extern int msgmake(struct MSGSTRUCT*);

/* follows snprintf() */
extern int msgprint(char*,int,int,int,char**,int);
/* buffer, length, msgnum, msgc, msgv, flag */

extern int msgclose();

typedef struct MSGSTRUCT
  {
    int  msgnum;        /* message number */
    int  msgc;          /* count of replacement tokens */
    char **msgv;        /* vector of replacement tokens */
    static unsigned char *msgbuf;   /* supplied by caller */
    int  msglen;        /* buffer size on input, msg length on return */
    static unsigned char *msgtext;   /* offset past msg code/header */

    int  msgfmt;        /* message format number (for future use) */
    int  msgline;       /* message line number (for future use, zero means all) */
    int  msglevel;      /* message level/serverity (zero means use the letter in the file) */

    char *applid;       /* default is basename of messages file */
    char *caller;       /* default is getenv("LOGNAME") roughly, msgu */
    char *prefix;       /* default is applid[0..2]||caller[0..2] */
    char *letter;       /* default taken from message file */

    /* the following are filled in by msgopen() not for user */
    int  msgmax;        /* highest message number in table */
    char **msgtable;
    char *msgdata,;
    char  pfxa[4];      /* truncated up-cased applid */
    char  pfxc[4];      /* truncated up-cased caller */
    char  locale[24];   /* possibly truncated to match the nearest file found */

  } MSGSTRUCT;


int sprintm(char*,int,char*,char*,int,char,int,char**);

int msgread(char*,int,FILE*,char*,int,char,int,char**);

extern
FILE *dfopen(char*,char*);

#endif

