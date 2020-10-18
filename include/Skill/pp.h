class PP
{
public:
  void init_pp(int pp);
  void add_max_pp(int pp);
  bool add_cur_pp(int pp);
  bool sub_cur_pp(int pp=1);
  int get_cur_pp();
  int get_max_pp();
  bool pp_run_out();
private:
  int cur_pp;
  int max_pp;
};
