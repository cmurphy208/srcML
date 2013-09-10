/*

  Test cases for srcml_archive_set_*.
*/
#include <stdio.h>
#include <string.h>
#include <cassert>

#include <srcml.h>
#include <srcml_types.hpp>
#include <srcmlns.hpp>

int main(int argc, char * argv[]) {

  {

    srcml_archive * archive = srcml_create_archive();
    srcml_archive_set_encoding(archive, 0);
    assert(archive->encoding == 0);
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();
    srcml_archive_set_encoding(archive, "foo");
    assert(*archive->encoding == "foo");
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();
    srcml_archive_set_language(archive, 0);
    assert(archive->language == 0);
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();
    srcml_archive_set_language(archive, "foo");
    assert(*archive->language == "foo");
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();
    srcml_archive_set_filename(archive, 0);
    assert(archive->filename == 0);
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();
    srcml_archive_set_filename(archive, "foo");
    assert(*archive->filename == "foo");
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();
    srcml_archive_set_directory(archive, 0);
    assert(archive->directory == 0);
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();
    srcml_archive_set_directory(archive, "foo");
    assert(*archive->directory == "foo");
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();
    srcml_archive_set_version(archive, 0);
    assert(archive->version == 0);
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();
    srcml_archive_set_version(archive, "foo");
    assert(*archive->version == "foo");
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();
    const char * attr[3][2] = { "foo", "bar", "", "", 0, 0 };

    srcml_archive_set_attributes(archive, attr);

    assert(archive->attributes.size() == 4);
    assert(archive->attributes.at(0) == "foo");
    assert(archive->attributes.at(1) == "bar");
    assert(archive->attributes.at(2) == "");
    assert(archive->attributes.at(3) == "");
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();
    const char * attr[3][2] = { "foo", "bar", "", 0, 0, 0 };

    srcml_archive_set_attributes(archive, attr);

    assert(archive->attributes.size() == 0);
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();

    srcml_archive_set_options(archive, 1 | 2 | 4);

    assert(archive->options == (1 | 2 | 4));
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();

    srcml_archive_set_options(archive, 1 | 2 | 4);
    srcml_archive_set_options(archive, 1);

    assert(archive->options == 1);
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();

    srcml_archive_set_option(archive, 1);

    assert(archive->options == 1);
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();

    srcml_archive_set_options(archive, 1 | 2);
    srcml_archive_set_option(archive, 4);

    assert(archive->options == (1 | 2 | 4));
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();

    srcml_archive_set_options(archive, 1);
    srcml_archive_set_option(archive, 2 | 4);

    assert(archive->options == (1 | 2 | 4));
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();

    srcml_archive_clear_option(archive, 0);

    assert(archive->options == 0);
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();

    srcml_archive_set_options(archive, 1 | 2 | 4);
    srcml_archive_clear_option(archive, 0);

    assert(archive->options == (1 | 2 | 4));
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();

    srcml_archive_set_options(archive, 1 | 2 | 4);
    srcml_archive_clear_option(archive, 2);

    assert(archive->options == (1 | 4));
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();

    srcml_archive_set_options(archive, 1 | 2 | 4);
    srcml_archive_clear_option(archive, 1 | 2);

    assert(archive->options == 4);
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();

    srcml_archive_set_tabstop(archive, 4);

    assert(archive->tabstop == 4);
    srcml_free_archive(archive);
  }

  {

    srcml_archive * archive = srcml_create_archive();

    srcml_archive_register_file_extension(archive, "foo", "C++");

    assert(archive->registered_languages.back().s == "foo");
    assert(archive->registered_languages.back().n == 2);
    srcml_free_archive(archive);
  }

  return 0;
}
