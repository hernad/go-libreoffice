#ifdef __cplusplus 
  extern "C" { 
#endif 


typedef struct _LibreOfficeG LibreOfficeG;
typedef struct _LibreOfficeDocumentG LibreOfficeDocumentG;

struct _LibreOfficeG {
  int  nSize;

  // destroy strukture
  void                 (*destroy)       (LibreOfficeG *pThis);

  // inicijalizacijska funkcija
  int                  (*initialize)    (LibreOfficeG *pThis,
                                         const char *pInstallPath);

  LibreOfficeDocumentG *(*documentLoad)  (LibreOfficeG *pThis,
                                         const char *pURL);
  char *               (*getError)      (LibreOfficeG *pThis);
};

struct _LibreOfficeDocumentG {
  int  nSize;

  void (*destroy)   (LibreOfficeDocumentG *pThis);
  int (*saveAs)     (LibreOfficeDocumentG *pThis,
                     const char *pUrl, const char *pFormat);
};

LibreOfficeG *libsoffice_init(const char *install_path);

LibreOfficeG *libreoffice_hook_g(void);
#ifdef __cplusplus 
  }
#endif 

