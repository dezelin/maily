// This code was generated by CLI, a command line interface
// compiler for C++.
//

namespace cli
{
  // unknown_mode
  //
  inline unknown_mode::
  unknown_mode (value v)
  : v_ (v)
  {
  }

  // exception
  //
  inline std::ostream&
  operator<< (std::ostream& os, const exception& e)
  {
    e.print (os);
    return os;
  }

  // unknown_option
  //
  inline unknown_option::
  unknown_option (const std::string& option)
  : option_ (option)
  {
  }

  inline const std::string& unknown_option::
  option () const
  {
    return option_;
  }

  // unknown_argument
  //
  inline unknown_argument::
  unknown_argument (const std::string& argument)
  : argument_ (argument)
  {
  }

  inline const std::string& unknown_argument::
  argument () const
  {
    return argument_;
  }

  // missing_value
  //
  inline missing_value::
  missing_value (const std::string& option)
  : option_ (option)
  {
  }

  inline const std::string& missing_value::
  option () const
  {
    return option_;
  }

  // invalid_value
  //
  inline invalid_value::
  invalid_value (const std::string& option,
                 const std::string& value)
  : option_ (option),  value_ (value)
  {
  }

  inline const std::string& invalid_value::
  option () const
  {
    return option_;
  }

  inline const std::string& invalid_value::
  value () const
  {
    return value_;
  }

  // file_io_failure
  //
  inline file_io_failure::
  file_io_failure (const std::string& file)
  : file_ (file)
  {
  }

  inline const std::string& file_io_failure::
  file () const
  {
    return file_;
  }

  // unmatched_quote
  //
  inline unmatched_quote::
  unmatched_quote (const std::string& argument)
  : argument_ (argument)
  {
  }

  inline const std::string& unmatched_quote::
  argument () const
  {
    return argument_;
  }

  // argv_scanner
  //
  inline argv_scanner::
  argv_scanner (int& argc, char** argv, bool erase)
  : i_ (1), argc_ (argc), argv_ (argv), erase_ (erase)
  {
  }

  inline argv_scanner::
  argv_scanner (int start, int& argc, char** argv, bool erase)
  : i_ (start), argc_ (argc), argv_ (argv), erase_ (erase)
  {
  }

  inline int argv_scanner::
  end () const
  {
    return i_;
  }

  // argv_file_scanner
  //
  inline argv_file_scanner::
  argv_file_scanner (int& argc,
                     char** argv,
                     const std::string& option,
                     bool erase)
  : argv_scanner (argc, argv, erase),
    option_ (option),
    options_ (&option_info_),
    options_count_ (1),
    skip_ (false)
  {
    option_info_.option = option_.c_str ();
    option_info_.search_func = 0;
  }

  inline argv_file_scanner::
  argv_file_scanner (int start,
                     int& argc,
                     char** argv,
                     const std::string& option,
                     bool erase)
  : argv_scanner (start, argc, argv, erase),
    option_ (option),
    options_ (&option_info_),
    options_count_ (1),
    skip_ (false)
  {
    option_info_.option = option_.c_str ();
    option_info_.search_func = 0;
  }

  inline argv_file_scanner::
  argv_file_scanner (int& argc,
                     char** argv,
                     const option_info* options,
                     std::size_t options_count,
                     bool erase)
  : argv_scanner (argc, argv, erase),
    options_ (options),
    options_count_ (options_count),
    skip_ (false)
  {
  }

  inline argv_file_scanner::
  argv_file_scanner (int start,
                     int& argc,
                     char** argv,
                     const option_info* options,
                     std::size_t options_count,
                     bool erase)
  : argv_scanner (start, argc, argv, erase),
    options_ (options),
    options_count_ (options_count),
    skip_ (false)
  {
  }

  inline const std::string& option::
  name () const
  {
    return name_;
  }

  inline const option_names& option::
  aliases () const
  {
    return aliases_;
  }

  inline bool option::
  flag () const
  {
    return flag_;
  }

  inline const std::string& option::
  default_value () const
  {
    return default_value_;
  }

  inline option::
  option ()
  {
  }

  inline option::
  option (const std::string& n,
          const option_names& a,
          bool f,
          const std::string& dv)
  : name_ (n), aliases_ (a), flag_ (f), default_value_ (dv)
  {
  }

  inline options::container_type::const_iterator options::
  find (const std::string& name) const
  {
    map_type::const_iterator i (map_.find (name));
    return i != map_.end () ? begin () + i->second : end ();
  }
}

// options
//

inline const bool& options::
help () const
{
  return this->help_;
}

inline void options::
help(const bool& x)
{
  this->help_ = x;
}

inline const bool& options::
version () const
{
  return this->version_;
}

inline void options::
version(const bool& x)
{
  this->version_ = x;
}

inline const std::vector<std::string>& options::
I () const
{
  return this->I_;
}

inline void options::
I(const std::vector<std::string>& x)
{
  this->I_ = x;
}

inline bool options::
I_specified () const
{
  return this->I_specified_;
}

inline void options::
I_specified(bool x)
{
  this->I_specified_ = x;
}

inline const std::vector<std::string>& options::
D () const
{
  return this->D_;
}

inline void options::
D(const std::vector<std::string>& x)
{
  this->D_ = x;
}

inline bool options::
D_specified () const
{
  return this->D_specified_;
}

inline void options::
D_specified(bool x)
{
  this->D_specified_ = x;
}

inline const std::vector<std::string>& options::
U () const
{
  return this->U_;
}

inline void options::
U(const std::vector<std::string>& x)
{
  this->U_ = x;
}

inline bool options::
U_specified () const
{
  return this->U_specified_;
}

inline void options::
U_specified(bool x)
{
  this->U_specified_ = x;
}

inline const ::database& options::
database () const
{
  return this->database_;
}

inline void options::
database(const ::database& x)
{
  this->database_ = x;
}

inline bool options::
database_specified () const
{
  return this->database_specified_;
}

inline void options::
database_specified(bool x)
{
  this->database_specified_ = x;
}

inline const bool& options::
generate_query () const
{
  return this->generate_query_;
}

inline void options::
generate_query(const bool& x)
{
  this->generate_query_ = x;
}

inline const bool& options::
generate_schema () const
{
  return this->generate_schema_;
}

inline void options::
generate_schema(const bool& x)
{
  this->generate_schema_ = x;
}

inline const std::set< ::schema_format>& options::
schema_format () const
{
  return this->schema_format_;
}

inline void options::
schema_format(const std::set< ::schema_format>& x)
{
  this->schema_format_ = x;
}

inline bool options::
schema_format_specified () const
{
  return this->schema_format_specified_;
}

inline void options::
schema_format_specified(bool x)
{
  this->schema_format_specified_ = x;
}

inline const std::string& options::
default_schema () const
{
  return this->default_schema_;
}

inline void options::
default_schema(const std::string& x)
{
  this->default_schema_ = x;
}

inline bool options::
default_schema_specified () const
{
  return this->default_schema_specified_;
}

inline void options::
default_schema_specified(bool x)
{
  this->default_schema_specified_ = x;
}

inline const std::string& options::
default_pointer () const
{
  return this->default_pointer_;
}

inline void options::
default_pointer(const std::string& x)
{
  this->default_pointer_ = x;
}

inline bool options::
default_pointer_specified () const
{
  return this->default_pointer_specified_;
}

inline void options::
default_pointer_specified(bool x)
{
  this->default_pointer_specified_ = x;
}

inline const std::string& options::
profile () const
{
  return this->profile_;
}

inline void options::
profile(const std::string& x)
{
  this->profile_ = x;
}

inline bool options::
profile_specified () const
{
  return this->profile_specified_;
}

inline void options::
profile_specified(bool x)
{
  this->profile_specified_ = x;
}

inline const std::string& options::
table_prefix () const
{
  return this->table_prefix_;
}

inline void options::
table_prefix(const std::string& x)
{
  this->table_prefix_ = x;
}

inline bool options::
table_prefix_specified () const
{
  return this->table_prefix_specified_;
}

inline void options::
table_prefix_specified(bool x)
{
  this->table_prefix_specified_ = x;
}

inline const std::string& options::
output_dir () const
{
  return this->output_dir_;
}

inline void options::
output_dir(const std::string& x)
{
  this->output_dir_ = x;
}

inline bool options::
output_dir_specified () const
{
  return this->output_dir_specified_;
}

inline void options::
output_dir_specified(bool x)
{
  this->output_dir_specified_ = x;
}

inline const std::string& options::
odb_file_suffix () const
{
  return this->odb_file_suffix_;
}

inline void options::
odb_file_suffix(const std::string& x)
{
  this->odb_file_suffix_ = x;
}

inline bool options::
odb_file_suffix_specified () const
{
  return this->odb_file_suffix_specified_;
}

inline void options::
odb_file_suffix_specified(bool x)
{
  this->odb_file_suffix_specified_ = x;
}

inline const std::string& options::
hxx_suffix () const
{
  return this->hxx_suffix_;
}

inline void options::
hxx_suffix(const std::string& x)
{
  this->hxx_suffix_ = x;
}

inline bool options::
hxx_suffix_specified () const
{
  return this->hxx_suffix_specified_;
}

inline void options::
hxx_suffix_specified(bool x)
{
  this->hxx_suffix_specified_ = x;
}

inline const std::string& options::
ixx_suffix () const
{
  return this->ixx_suffix_;
}

inline void options::
ixx_suffix(const std::string& x)
{
  this->ixx_suffix_ = x;
}

inline bool options::
ixx_suffix_specified () const
{
  return this->ixx_suffix_specified_;
}

inline void options::
ixx_suffix_specified(bool x)
{
  this->ixx_suffix_specified_ = x;
}

inline const std::string& options::
cxx_suffix () const
{
  return this->cxx_suffix_;
}

inline void options::
cxx_suffix(const std::string& x)
{
  this->cxx_suffix_ = x;
}

inline bool options::
cxx_suffix_specified () const
{
  return this->cxx_suffix_specified_;
}

inline void options::
cxx_suffix_specified(bool x)
{
  this->cxx_suffix_specified_ = x;
}

inline const std::string& options::
sql_suffix () const
{
  return this->sql_suffix_;
}

inline void options::
sql_suffix(const std::string& x)
{
  this->sql_suffix_ = x;
}

inline bool options::
sql_suffix_specified () const
{
  return this->sql_suffix_specified_;
}

inline void options::
sql_suffix_specified(bool x)
{
  this->sql_suffix_specified_ = x;
}

inline const std::vector<std::string>& options::
hxx_prologue () const
{
  return this->hxx_prologue_;
}

inline void options::
hxx_prologue(const std::vector<std::string>& x)
{
  this->hxx_prologue_ = x;
}

inline bool options::
hxx_prologue_specified () const
{
  return this->hxx_prologue_specified_;
}

inline void options::
hxx_prologue_specified(bool x)
{
  this->hxx_prologue_specified_ = x;
}

inline const std::vector<std::string>& options::
ixx_prologue () const
{
  return this->ixx_prologue_;
}

inline void options::
ixx_prologue(const std::vector<std::string>& x)
{
  this->ixx_prologue_ = x;
}

inline bool options::
ixx_prologue_specified () const
{
  return this->ixx_prologue_specified_;
}

inline void options::
ixx_prologue_specified(bool x)
{
  this->ixx_prologue_specified_ = x;
}

inline const std::vector<std::string>& options::
cxx_prologue () const
{
  return this->cxx_prologue_;
}

inline void options::
cxx_prologue(const std::vector<std::string>& x)
{
  this->cxx_prologue_ = x;
}

inline bool options::
cxx_prologue_specified () const
{
  return this->cxx_prologue_specified_;
}

inline void options::
cxx_prologue_specified(bool x)
{
  this->cxx_prologue_specified_ = x;
}

inline const std::vector<std::string>& options::
sql_prologue () const
{
  return this->sql_prologue_;
}

inline void options::
sql_prologue(const std::vector<std::string>& x)
{
  this->sql_prologue_ = x;
}

inline bool options::
sql_prologue_specified () const
{
  return this->sql_prologue_specified_;
}

inline void options::
sql_prologue_specified(bool x)
{
  this->sql_prologue_specified_ = x;
}

inline const std::vector<std::string>& options::
hxx_epilogue () const
{
  return this->hxx_epilogue_;
}

inline void options::
hxx_epilogue(const std::vector<std::string>& x)
{
  this->hxx_epilogue_ = x;
}

inline bool options::
hxx_epilogue_specified () const
{
  return this->hxx_epilogue_specified_;
}

inline void options::
hxx_epilogue_specified(bool x)
{
  this->hxx_epilogue_specified_ = x;
}

inline const std::vector<std::string>& options::
ixx_epilogue () const
{
  return this->ixx_epilogue_;
}

inline void options::
ixx_epilogue(const std::vector<std::string>& x)
{
  this->ixx_epilogue_ = x;
}

inline bool options::
ixx_epilogue_specified () const
{
  return this->ixx_epilogue_specified_;
}

inline void options::
ixx_epilogue_specified(bool x)
{
  this->ixx_epilogue_specified_ = x;
}

inline const std::vector<std::string>& options::
cxx_epilogue () const
{
  return this->cxx_epilogue_;
}

inline void options::
cxx_epilogue(const std::vector<std::string>& x)
{
  this->cxx_epilogue_ = x;
}

inline bool options::
cxx_epilogue_specified () const
{
  return this->cxx_epilogue_specified_;
}

inline void options::
cxx_epilogue_specified(bool x)
{
  this->cxx_epilogue_specified_ = x;
}

inline const std::vector<std::string>& options::
sql_epilogue () const
{
  return this->sql_epilogue_;
}

inline void options::
sql_epilogue(const std::vector<std::string>& x)
{
  this->sql_epilogue_ = x;
}

inline bool options::
sql_epilogue_specified () const
{
  return this->sql_epilogue_specified_;
}

inline void options::
sql_epilogue_specified(bool x)
{
  this->sql_epilogue_specified_ = x;
}

inline const std::string& options::
hxx_prologue_file () const
{
  return this->hxx_prologue_file_;
}

inline void options::
hxx_prologue_file(const std::string& x)
{
  this->hxx_prologue_file_ = x;
}

inline bool options::
hxx_prologue_file_specified () const
{
  return this->hxx_prologue_file_specified_;
}

inline void options::
hxx_prologue_file_specified(bool x)
{
  this->hxx_prologue_file_specified_ = x;
}

inline const std::string& options::
ixx_prologue_file () const
{
  return this->ixx_prologue_file_;
}

inline void options::
ixx_prologue_file(const std::string& x)
{
  this->ixx_prologue_file_ = x;
}

inline bool options::
ixx_prologue_file_specified () const
{
  return this->ixx_prologue_file_specified_;
}

inline void options::
ixx_prologue_file_specified(bool x)
{
  this->ixx_prologue_file_specified_ = x;
}

inline const std::string& options::
cxx_prologue_file () const
{
  return this->cxx_prologue_file_;
}

inline void options::
cxx_prologue_file(const std::string& x)
{
  this->cxx_prologue_file_ = x;
}

inline bool options::
cxx_prologue_file_specified () const
{
  return this->cxx_prologue_file_specified_;
}

inline void options::
cxx_prologue_file_specified(bool x)
{
  this->cxx_prologue_file_specified_ = x;
}

inline const std::string& options::
sql_prologue_file () const
{
  return this->sql_prologue_file_;
}

inline void options::
sql_prologue_file(const std::string& x)
{
  this->sql_prologue_file_ = x;
}

inline bool options::
sql_prologue_file_specified () const
{
  return this->sql_prologue_file_specified_;
}

inline void options::
sql_prologue_file_specified(bool x)
{
  this->sql_prologue_file_specified_ = x;
}

inline const std::string& options::
hxx_epilogue_file () const
{
  return this->hxx_epilogue_file_;
}

inline void options::
hxx_epilogue_file(const std::string& x)
{
  this->hxx_epilogue_file_ = x;
}

inline bool options::
hxx_epilogue_file_specified () const
{
  return this->hxx_epilogue_file_specified_;
}

inline void options::
hxx_epilogue_file_specified(bool x)
{
  this->hxx_epilogue_file_specified_ = x;
}

inline const std::string& options::
ixx_epilogue_file () const
{
  return this->ixx_epilogue_file_;
}

inline void options::
ixx_epilogue_file(const std::string& x)
{
  this->ixx_epilogue_file_ = x;
}

inline bool options::
ixx_epilogue_file_specified () const
{
  return this->ixx_epilogue_file_specified_;
}

inline void options::
ixx_epilogue_file_specified(bool x)
{
  this->ixx_epilogue_file_specified_ = x;
}

inline const std::string& options::
cxx_epilogue_file () const
{
  return this->cxx_epilogue_file_;
}

inline void options::
cxx_epilogue_file(const std::string& x)
{
  this->cxx_epilogue_file_ = x;
}

inline bool options::
cxx_epilogue_file_specified () const
{
  return this->cxx_epilogue_file_specified_;
}

inline void options::
cxx_epilogue_file_specified(bool x)
{
  this->cxx_epilogue_file_specified_ = x;
}

inline const std::string& options::
sql_epilogue_file () const
{
  return this->sql_epilogue_file_;
}

inline void options::
sql_epilogue_file(const std::string& x)
{
  this->sql_epilogue_file_ = x;
}

inline bool options::
sql_epilogue_file_specified () const
{
  return this->sql_epilogue_file_specified_;
}

inline void options::
sql_epilogue_file_specified(bool x)
{
  this->sql_epilogue_file_specified_ = x;
}

inline const std::vector<std::string>& options::
odb_prologue () const
{
  return this->odb_prologue_;
}

inline void options::
odb_prologue(const std::vector<std::string>& x)
{
  this->odb_prologue_ = x;
}

inline bool options::
odb_prologue_specified () const
{
  return this->odb_prologue_specified_;
}

inline void options::
odb_prologue_specified(bool x)
{
  this->odb_prologue_specified_ = x;
}

inline const std::vector<std::string>& options::
odb_prologue_file () const
{
  return this->odb_prologue_file_;
}

inline void options::
odb_prologue_file(const std::vector<std::string>& x)
{
  this->odb_prologue_file_ = x;
}

inline bool options::
odb_prologue_file_specified () const
{
  return this->odb_prologue_file_specified_;
}

inline void options::
odb_prologue_file_specified(bool x)
{
  this->odb_prologue_file_specified_ = x;
}

inline const std::vector<std::string>& options::
odb_epilogue () const
{
  return this->odb_epilogue_;
}

inline void options::
odb_epilogue(const std::vector<std::string>& x)
{
  this->odb_epilogue_ = x;
}

inline bool options::
odb_epilogue_specified () const
{
  return this->odb_epilogue_specified_;
}

inline void options::
odb_epilogue_specified(bool x)
{
  this->odb_epilogue_specified_ = x;
}

inline const std::vector<std::string>& options::
odb_epilogue_file () const
{
  return this->odb_epilogue_file_;
}

inline void options::
odb_epilogue_file(const std::vector<std::string>& x)
{
  this->odb_epilogue_file_ = x;
}

inline bool options::
odb_epilogue_file_specified () const
{
  return this->odb_epilogue_file_specified_;
}

inline void options::
odb_epilogue_file_specified(bool x)
{
  this->odb_epilogue_file_specified_ = x;
}

inline const bool& options::
include_with_brackets () const
{
  return this->include_with_brackets_;
}

inline void options::
include_with_brackets(const bool& x)
{
  this->include_with_brackets_ = x;
}

inline const std::string& options::
include_prefix () const
{
  return this->include_prefix_;
}

inline void options::
include_prefix(const std::string& x)
{
  this->include_prefix_ = x;
}

inline bool options::
include_prefix_specified () const
{
  return this->include_prefix_specified_;
}

inline void options::
include_prefix_specified(bool x)
{
  this->include_prefix_specified_ = x;
}

inline const std::vector<std::string>& options::
include_regex () const
{
  return this->include_regex_;
}

inline void options::
include_regex(const std::vector<std::string>& x)
{
  this->include_regex_ = x;
}

inline bool options::
include_regex_specified () const
{
  return this->include_regex_specified_;
}

inline void options::
include_regex_specified(bool x)
{
  this->include_regex_specified_ = x;
}

inline const bool& options::
include_regex_trace () const
{
  return this->include_regex_trace_;
}

inline void options::
include_regex_trace(const bool& x)
{
  this->include_regex_trace_ = x;
}

inline const std::string& options::
guard_prefix () const
{
  return this->guard_prefix_;
}

inline void options::
guard_prefix(const std::string& x)
{
  this->guard_prefix_ = x;
}

inline bool options::
guard_prefix_specified () const
{
  return this->guard_prefix_specified_;
}

inline void options::
guard_prefix_specified(bool x)
{
  this->guard_prefix_specified_ = x;
}

inline const std::string& options::
options_file () const
{
  return this->options_file_;
}

inline void options::
options_file(const std::string& x)
{
  this->options_file_ = x;
}

inline bool options::
options_file_specified () const
{
  return this->options_file_specified_;
}

inline void options::
options_file_specified(bool x)
{
  this->options_file_specified_ = x;
}

inline const std::vector<std::string>& options::
x () const
{
  return this->x_;
}

inline void options::
x(const std::vector<std::string>& x)
{
  this->x_ = x;
}

inline bool options::
x_specified () const
{
  return this->x_specified_;
}

inline void options::
x_specified(bool x)
{
  this->x_specified_ = x;
}

inline const bool& options::
v () const
{
  return this->v_;
}

inline void options::
v(const bool& x)
{
  this->v_ = x;
}

inline const bool& options::
trace () const
{
  return this->trace_;
}

inline void options::
trace(const bool& x)
{
  this->trace_ = x;
}

inline const std::string& options::
mysql_engine () const
{
  return this->mysql_engine_;
}

inline void options::
mysql_engine(const std::string& x)
{
  this->mysql_engine_ = x;
}

inline bool options::
mysql_engine_specified () const
{
  return this->mysql_engine_specified_;
}

inline void options::
mysql_engine_specified(bool x)
{
  this->mysql_engine_specified_ = x;
}

inline const bool& options::
sqlite_lax_auto_id () const
{
  return this->sqlite_lax_auto_id_;
}

inline void options::
sqlite_lax_auto_id(const bool& x)
{
  this->sqlite_lax_auto_id_ = x;
}

inline const ::oracle_version& options::
oracle_client_version () const
{
  return this->oracle_client_version_;
}

inline void options::
oracle_client_version(const ::oracle_version& x)
{
  this->oracle_client_version_ = x;
}

inline bool options::
oracle_client_version_specified () const
{
  return this->oracle_client_version_specified_;
}

inline void options::
oracle_client_version_specified(bool x)
{
  this->oracle_client_version_specified_ = x;
}

