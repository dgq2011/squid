#if ICAP_CLIENT
#include "ICAP/ICAPServiceRep.h"
#endif

class ClientRequestContext : public RefCountable
{

public:
    void *operator new(size_t);
    void operator delete(void *);

    ClientRequestContext(ClientHttpRequest *);
    ~ClientRequestContext();

    bool httpStateIsValid();
    void clientAccessCheck();
    void clientAccessCheckDone(int answer);
    void clientRedirectStart();
    void clientRedirectDone(char *result);
    void checkNoCache();
    void checkNoCacheDone(int answer);
#if ICAP_CLIENT

    void icapAccessCheck();
    void icapAclCheckDone(ICAPServiceRep::Pointer service);
#endif

    ClientHttpRequest *http;
    ACLChecklist *acl_checklist;        /* need ptr back so we can unreg if needed */
    int redirect_state;

int http_access_done:
    1;
#if ICAP_CLIENT

int icap_acl_check_done:
    1;
#endif

int redirect_done:
    1;

int no_cache_done:
    1;

private:
    CBDATA_CLASS(ClientRequestContext);
};

