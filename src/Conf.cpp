/*
 * libdigidocpp
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "Conf.h"

#include "crypto/Digest.h"
#include "crypto/X509Cert.h"
#include "tslcerts.h"
#include "util/File.h"
#include "util/log.h"

#include <map>

using namespace digidoc;
using namespace digidoc::util;
using namespace std;

Conf* Conf::INSTANCE = nullptr;

/**
 * @typedef digidoc::ConfCurrent
 * @see digidoc::ConfV5
 */

/**
 * @class digidoc::Conf
 * @brief Configuration class which can reimplemented and virtual methods overloaded.
 *
 * @deprecated Use digidoc::ConfV5
 * @see @ref parameters
 */
/**
 * Configuration parameters
 */
Conf::Conf() = default;

Conf::~Conf() = default;

/**
 * Return global config instance object
 */
Conf* Conf::instance() { return INSTANCE; }

/**
 * Init global Conf with conf
 */
void Conf::init(Conf *conf)
{
    delete INSTANCE;
    INSTANCE = conf;
}

/**
 * Returns libdigidoc library configuration file's (digidoc.ini) file location
 * @deprecated Unused
 */
string Conf::libdigidocConf() const { return {}; }

/**
 * Returns log level.
 * 0 = Error
 * 1 = Warn
 * 2 = Info
 * 3 = Debug
 */
int Conf::logLevel() const {
#ifdef NDEBUG
    return Log::InfoType;
#else
    return Log::DebugType;
#endif
}

/**
 * Gets log file location. Default log goes to standard out stream
 */
string Conf::logFile() const { return {}; }

/**
 * Return default digest type as URI
 */
string Conf::digestUri() const { return URI_SHA256; }

/**
 * Gets XSD schema files path
 */
string Conf::xsdPath() const { return File::path(File::confPath(), "schema"); }

/**
 * Returns PKCS11 driver file path
 */
string Conf::PKCS11Driver() const { return PKCS11_MODULE; }

/**
 * Return OCSP request URL
 * @param issuer OCSP issuer.
 */
string Conf::ocsp(const string &/*issuer*/) const
{
    return {};
}

/**
 * Gets Certificate store location.
 * @deprecated Unused
 */
string Conf::certsPath() const { return {}; }

/**
 * Gets proxy host address.
 */
string Conf::proxyHost() const { return {}; }

/**
 * Gets proxy port number.
 */
string Conf::proxyPort() const { return {}; }

/**
 * Gets proxy user name.
 */
string Conf::proxyUser() const { return {}; }

/**
 * Gets proxy login password.
 */
string Conf::proxyPass() const { return {}; }

/**
 * Gets PKCS12 certificate file location.
 *
 * Used for signing OCSP request
 */
string Conf::PKCS12Cert() const { return {}; }

/**
 * Gets PKCS12 password.
 * @see digidoc::Conf::PKCS12Cert
 */
string Conf::PKCS12Pass() const { return {}; }

/**
 * Gets PKCS12 usage.
 * @see digidoc::Conf::PKCS12Cert
 */
bool Conf::PKCS12Disable() const { return false; }

/**
 * Returns default time-stamp server URL
 */
string Conf::TSUrl() const { return TSA_URL; }

/**
 * Download new TSL list when it is expired or invalid
 */
bool Conf::TSLAutoUpdate() const { return true; }

/**
 * TSL cache path in local file system
 */
string Conf::TSLCache() const
{
    return File::path(File::digidocppPath(), "tsl");
}

/**
 * TSL master list's (LOTL) URL
 */
string Conf::TSLUrl() const { return TSL_URL; }

/**
 * Allow expired TSL lists
 */
bool Conf::TSLAllowExpired() const { return false; }

/**
 * TSL master list's (LOTL) signing certificates
 */
vector<X509Cert> Conf::TSLCerts() const { return tslcerts; }

/**
 * Compare local TSL digest with digest published online to check for newer version
 */
bool Conf::TSLOnlineDigest() const { return true; }

/**
 * Gets TSL downloading connection's current timeout value
 */
int Conf::TSLTimeOut() const { return 10; }

/**
 * Redirect SSL traffic over proxy server
 * Default: false
 */
bool Conf::proxyForceSSL() const { return false; }

/**
 * Tunnel SSL traffic over proxy server
 * Default: false
 */
bool Conf::proxyTunnelSSL() const { return true; }

/**
 * Gets signature digest URI
 */
string Conf::signatureDigestUri() const { return digestUri(); }

/**
 * Gets verify service URI
 */
string Conf::verifyServiceUri() const { return SIVA_URL; }



/**
 * @class digidoc::ConfV2
 * @brief Verison 2 of configuration class to add additonial parameters.
 *
 * Conf contains virtual members and is not leaf class we need create
 * subclasses to keep binary compatibility
 * https://techbase.kde.org/Policies/Binary_Compatibility_Issues_With_C++#Adding_new_virtual_functions_to_leaf_classes
 * @see digidoc::Conf
 * @deprecated Use digidoc::ConfV5
 * @see @ref parameters
 */
/**
 * Version 2 config with new parameters
 */
ConfV2::ConfV2() = default;

ConfV2::~ConfV2() = default;

/**
 * @copydoc digidoc::Conf::instance()
 */
ConfV2* ConfV2::instance() { return dynamic_cast<ConfV2*>(Conf::instance()); }

/**
 * Gets verify service Cert
 */
X509Cert ConfV2::verifyServiceCert() const { return X509Cert(); }



/**
 * @class digidoc::ConfV3
 * @brief Verison 3 of configuration class to add additonial parameters.
 *
 * Conf contains virtual members and is not leaf class we need create
 * subclasses to keep binary compatibility
 * https://techbase.kde.org/Policies/Binary_Compatibility_Issues_With_C++#Adding_new_virtual_functions_to_leaf_classes
 * @see digidoc::ConfV2
 * @deprecated Use digidoc::ConfV5
 * @see @ref parameters
 */
/**
 * Version 3 config with new parameters
 */
ConfV3::ConfV3() = default;

ConfV3::~ConfV3() = default;

/**
 * @copydoc digidoc::Conf::instance()
 */
ConfV3* ConfV3::instance() { return dynamic_cast<ConfV3*>(Conf::instance()); }

/**
 * Gets OCSP TM Profile OID-s
 *
 * OCSP responder certificate policies that are used to identify if OCSP response is given with TM profile
 */
set<string> ConfV3::OCSPTMProfiles() const { return { "1.3.6.1.4.1.10015.4.1.2" }; }



/**
 * @class digidoc::ConfV4
 * @brief Verison 4 of configuration class to add additonial parameters.
 *
 * Conf contains virtual members and is not leaf class we need create
 * subclasses to keep binary compatibility
 * https://techbase.kde.org/Policies/Binary_Compatibility_Issues_With_C++#Adding_new_virtual_functions_to_leaf_classes
 * @see digidoc::ConfV3
 * @deprecated Use digidoc::ConfV5
 * @see @ref parameters
 */
/**
 * Version 4 config with new parameters
 */
ConfV4::ConfV4() = default;

ConfV4::~ConfV4() = default;

/**
 * @copydoc digidoc::Conf::instance()
 */
ConfV4* ConfV4::instance() { return dynamic_cast<ConfV4*>(Conf::instance()); }

/**
 * Gets verify service Certs
 */
vector<X509Cert> ConfV4::verifyServiceCerts() const
{
    if(X509Cert cert = verifyServiceCert())
        return { cert };
    return {};
}

/**
 * @class digidoc::ConfV5
 * @brief Verison 5 of configuration class to add additonial parameters.
 *
 * Conf contains virtual members and is not leaf class we need create
 * subclasses to keep binary compatibility
 * https://techbase.kde.org/Policies/Binary_Compatibility_Issues_With_C++#Adding_new_virtual_functions_to_leaf_classes
 * @see digidoc::ConfV4
 * @see @ref parameters
 */
/**
 * Version 4 config with new parameters
 */
ConfV5::ConfV5() = default;

ConfV5::~ConfV5() = default;

/**
 * @copydoc digidoc::Conf::instance()
 */
ConfV5* ConfV5::instance() { return dynamic_cast<ConfV5*>(Conf::instance()); }

/**
 * Gets verify service Certs
 */
vector<X509Cert> ConfV5::TSCerts() const
{
    return {};
}
