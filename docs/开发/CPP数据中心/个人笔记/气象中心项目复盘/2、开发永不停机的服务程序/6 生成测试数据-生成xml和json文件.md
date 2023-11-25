```c++
// 把容器vsurfdata中的全国气象站点分钟观测数据写入文件。
bool CrtSurfFile(const char *outpath,const char *datafmt)
{
  CFile File;

  // 拼接生成数据的文件名，例如：/tmp/idc/surfdata/SURF_ZH_20210629092200_2254.csv
  char strFileName[301];
  sprintf(strFileName,"%s/SURF_ZH_%s_%d.%s",outpath,strddatetime,getpid(),datafmt);

  // 打开文件。
  if (File.OpenForRename(strFileName,"w")==false)
  {
    logfile.Write("File.OpenForRename(%s) failed.\n",strFileName); return false;
  }

  if (strcmp(datafmt,"csv")==0) File.Fprintf("站点代码,数据时间,气温,气压,相对湿度,风向,风速,降雨量,能见度\n");
  if (strcmp(datafmt,"xml")==0) File.Fprintf("<data>\n");
  if (strcmp(datafmt,"json")==0) File.Fprintf("{\"data\":[\n");

  // 遍历存放观测数据的vsurfdata容器。
  for (int ii=0;ii<vsurfdata.size();ii++)
  {
    // 写入一条记录。
    if (strcmp(datafmt,"csv")==0)
      File.Fprintf("%s,%s,%.1f,%.1f,%d,%d,%.1f,%.1f,%.1f\n",\
         vsurfdata[ii].obtid,vsurfdata[ii].ddatetime,vsurfdata[ii].t/10.0,vsurfdata[ii].p/10.0,\
         vsurfdata[ii].u,vsurfdata[ii].wd,vsurfdata[ii].wf/10.0,vsurfdata[ii].r/10.0,vsurfdata[ii].vis/10.0);

    if (strcmp(datafmt,"xml")==0)
      File.Fprintf("<obtid>%s</obtid><ddatetime>%s</ddatetime><t>%.1f</t><p>%.1f</p>"\
                   "<u>%d</u><wd>%d</wd><wf>%.1f</wf><r>%.1f</r><vis>%.1f</vis><endl/>\n",\
         vsurfdata[ii].obtid,vsurfdata[ii].ddatetime,vsurfdata[ii].t/10.0,vsurfdata[ii].p/10.0,\
         vsurfdata[ii].u,vsurfdata[ii].wd,vsurfdata[ii].wf/10.0,vsurfdata[ii].r/10.0,vsurfdata[ii].vis/10.0);

    if (strcmp(datafmt,"json")==0)
      File.Fprintf("{\"obtid\":\"%s\",\"ddatetime\":\"%s\",\"t\":\"%.1f\",\"p\":\"%.1f\","\
                   "\"u\":\"%d\",\"wd\":\"%d\",\"wf\":\"%.1f\",\"r\":\"%.1f\",\"vis\":\"%.1f\"}",\
         vsurfdata[ii].obtid,vsurfdata[ii].ddatetime,vsurfdata[ii].t/10.0,vsurfdata[ii].p/10.0,\
         vsurfdata[ii].u,vsurfdata[ii].wd,vsurfdata[ii].wf/10.0,vsurfdata[ii].r/10.0,vsurfdata[ii].vis/10.0);
    if (ii<vsurfdata.size()-1) File.Fprintf(",\n");
    else   File.Fprintf("\n");
    // 以上几行代码有bug，应该修正如下：
    /*
    if (strcmp(datafmt,"json")==0)
    {
      File.Fprintf("{\"obtid\":\"%s\",\"ddatetime\":\"%s\",\"t\":\"%.1f\",\"p\":\"%.1f\","\
                   "\"u\":\"%d\",\"wd\":\"%d\",\"wf\":\"%.1f\",\"r\":\"%.1f\",\"vis\":\"%.1f\"}",\
         vsurfdata[ii].obtid,vsurfdata[ii].ddatetime,vsurfdata[ii].t/10.0,vsurfdata[ii].p/10.0,\
         vsurfdata[ii].u,vsurfdata[ii].wd,vsurfdata[ii].wf/10.0,vsurfdata[ii].r/10.0,vsurfdata[ii].vis/10.0);
      if (ii<vsurfdata.size()-1) File.Fprintf(",\n");
      else   File.Fprintf("\n");
    }
    */
  }

  if (strcmp(datafmt,"xml")==0) File.Fprintf("</data>\n");
  if (strcmp(datafmt,"json")==0) File.Fprintf("]}\n");

  // 关闭文件。
  File.CloseAndRename();

  logfile.Write("生成数据文件%s成功，数据时间%s，记录数%d。\n",strFileName,strddatetime,vsurfdata.size());

  return true;
}
```

