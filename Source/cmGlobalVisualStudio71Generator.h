/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#ifndef cmGlobalVisualStudio71Generator_h
#define cmGlobalVisualStudio71Generator_h

#include "cmGlobalVisualStudio7Generator.h"

/** \class cmGlobalVisualStudio71Generator
 * \brief Write a Unix makefiles.
 *
 * cmGlobalVisualStudio71Generator manages UNIX build process for a tree
 */
class cmGlobalVisualStudio71Generator : public cmGlobalVisualStudio7Generator
{
public:
  cmGlobalVisualStudio71Generator(cmake* cm,
                                  const std::string& platformName = "");
  static cmGlobalGeneratorFactory* NewFactory()
  {
    return new cmGlobalGeneratorSimpleFactory<
      cmGlobalVisualStudio71Generator>();
  }

  ///! Get the name for the generator.
  virtual std::string GetName() const
  {
    return cmGlobalVisualStudio71Generator::GetActualName();
  }
  static std::string GetActualName() { return "Visual Studio 7 .NET 2003"; }

  /** Get the documentation entry for this generator.  */
  static void GetDocumentation(cmDocumentationEntry& entry);

  /**
   * Where does this version of Visual Studio look for macros for the
   * current user? Returns the empty string if this version of Visual
   * Studio does not implement support for VB macros.
   */
  virtual std::string GetUserMacrosDirectory();

  /**
   * What is the reg key path to "vsmacros" for this version of Visual
   * Studio?
   */
  virtual std::string GetUserMacrosRegKeyBase();

protected:
  virtual const char* GetIDEVersion() { return "7.1"; }
  virtual void WriteSLNFile(std::ostream& fout, cmLocalGenerator* root,
                            std::vector<cmLocalGenerator*>& generators);
  virtual void WriteSolutionConfigurations(
    std::ostream& fout, std::vector<std::string> const& configs);
  virtual void WriteProject(std::ostream& fout, const std::string& name,
                            const char* path, const cmGeneratorTarget* t);
  virtual void WriteProjectDepends(std::ostream& fout, const std::string& name,
                                   const char* path,
                                   cmGeneratorTarget const* t);
  virtual void WriteProjectConfigurations(
    std::ostream& fout, const std::string& name,
    cmGeneratorTarget const& target, std::vector<std::string> const& configs,
    const std::set<std::string>& configsPartOfDefaultBuild,
    const std::string& platformMapping = "");
  virtual void WriteExternalProject(std::ostream& fout,
                                    const std::string& name, const char* path,
                                    const char* typeGuid,
                                    const std::set<std::string>& depends);
  virtual void WriteSLNHeader(std::ostream& fout);

  // Folders are not supported by VS 7.1.
  virtual bool UseFolderProperty() { return false; }

  std::string ProjectConfigurationSectionName;
};
#endif
