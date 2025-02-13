#ifndef __OFDPAGE_H__
#define __OFDPAGE_H__

#ifdef __cplusplus

#include "ofd.h"
#include <string>
#include <tuple>
#include <vector>

namespace ofd {

class OFDDocument;
class OFDObject;

class OFDPage {
  public:
    OFDPage(OFDDocument *ofdDocument, uint64_t id, const std::string &filename);
    ~OFDPage();

    bool Open();
    void Close();

    const OFDDocument *GetOFDDocument() const { return m_ofdDocument; };
    OFDDocument *GetOFDDocument() { return m_ofdDocument; };

    bool IsOpened() const { return m_opened; };

    size_t GetOFDObjectsCount() const { return m_ofdObjects.size(); };
    const OFDObject *GetOFDObject(size_t idx) const {
        return m_ofdObjects[idx];
    };
    OFDObject *GetOFDObject(size_t idx) { return m_ofdObjects[idx]; };

    uint64_t GetID() const { return m_id; };
    std::string GetText() const { return m_text; };

    bool RenderToPNGFile(const std::string &filename);

  public:
    struct OFDPageTemplate {
        uint64_t templateId;
        std::string zOrder;
    };
    struct Attributes {
        OFDPageArea PageArea;
        OFDPageTemplate PageTemplate;

        void clear() {
            memset((void *)&PageArea, 0, sizeof(PageArea));
            memset((void *)&PageTemplate, 0, sizeof(PageTemplate));
        }
    };

    const Attributes &GetAttributes() const { return m_attributes; };
    Attributes &GetAttributes() { return m_attributes; };

    std::string String() const;

  private:
    OFDDocument *m_ofdDocument;
    uint64_t m_id;
    std::string m_filename;

    Attributes m_attributes;

    bool m_opened = false;
    std::vector<OFDObject *> m_ofdObjects;
    std::string m_text;

    void clear();
    bool parseXML(const std::string &content);

}; // class OFDPage

} // namespace ofd

#endif // #ifdef __cplusplus

#endif // __OFDPAGE_H__
