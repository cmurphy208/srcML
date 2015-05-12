#include <srcmlns.hpp>

/**
 * is_srcml_namespace
 * @param uri the uri to compare
 * @param srcml_uri the srcML URI to compare to
 *
 * Compare uri to the srcML uri idependent of prefix
 * i.e., www.sdml.info or www.srcML.org.
 */
bool is_srcml_namespace(const std::string & uri, const std::string & srcml_uri) {

	if(uri == srcml_uri) return true;

	std::string uri_suffix = uri, srcml_uri_suffix = srcml_uri;

	for(int pos = 0; SRCML_URI_PREFIX[pos][0]; ++pos) {

		std::string::size_type str_pos = uri.find(SRCML_URI_PREFIX[pos]);
		if(str_pos == 0) {

			uri_suffix = uri.substr(SRCML_URI_PREFIX[pos].size());
			break;

		}

	}

	for(int pos = 0; SRCML_URI_PREFIX[pos][0]; ++pos) {

		std::string::size_type str_pos = srcml_uri.find(SRCML_URI_PREFIX[pos]);
		if(str_pos == 0) {

			srcml_uri_suffix = srcml_uri.substr(SRCML_URI_PREFIX[pos].size());
			break;

		}

	}

	return uri_suffix == srcml_uri_suffix;

}