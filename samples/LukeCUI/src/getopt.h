#ifndef GETOPT_H
#define GETOPT_H

/* Reference http://pokotsun.mydns.jp/?p=613 */

#include <cstdio>
#include <cstring>


#define ERR(szz,czz) if(m_opterr){fprintf(stderr,"%s%s%c\n",m_argv[0],szz,czz);}
 
class getoption {
public:
    explicit getoption( int argc, char* argv[] ) :
    m_argc( argc ),
    m_argv( argv ),
    m_sp( 1 ),
    m_opterr( 1 ),
    m_optind( 1 ),
    m_optopt( 0 ),
    m_optarg( 0 ) {
    }
 
    int get( char* opts ) {
        register int c;
        register char *cp;
 
        if (m_sp == 1) {
            if (m_optind >= m_argc || m_argv[m_optind][0] != '-' || m_argv[m_optind][1] == '\0')
                return (EOF);
            else if (strcmp(m_argv[m_optind], "--") == 0) {
                m_optind++;
                return (EOF);
            }
        }
        m_optopt = c = m_argv[m_optind][m_sp];
        if (c == ':' || (cp=std::strchr(opts, c)) == NULL) {
            ERR(": illegal option -- ", c);
            if (m_argv[m_optind][++m_sp] == '\0') {
                m_optind++;
                m_sp = 1;
            }
            return ('?');
        }
       if (*++cp == ':') {
            if (m_argv[m_optind][m_sp+1] != '\0') {
                m_optarg = &m_argv[m_optind++][m_sp+1];
            }
            else if (++m_optind >= m_argc) {
                ERR(": option requires an argument -- ", c);
                m_sp = 1;
                return ('?');
            }
            else {
             m_optarg = m_argv[m_optind++];
            }
            m_sp = 1;
       }
       else {
            if (m_argv[m_optind][++m_sp] == '\0') {
             m_sp = 1;
             m_optind++;
            }
            m_optarg = NULL;
        }
        return (c);
    }
 
    char* argument() {
        return m_optarg;
    }
 
    int optind() {
        return m_optind;
    }
 
private:
    int     m_argc;
    char**  m_argv;
    int     m_sp;
 
    int     m_opterr;
    int     m_optind;
    int     m_optopt;
    char*   m_optarg;
};

#endif
