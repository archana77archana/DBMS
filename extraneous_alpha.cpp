//@author archana77

#include<map>
#include<set>
#include<iostream>
#include<string>
#include<stdlib.h>
#include<vector>

using namespace std;

class Graph
{
   map<string,set<char> > graph;   

   public:
   
   string string_maker(string s, int n)
   {
     string res = "";
     res = s.substr(0,n)+s.substr(n+1);
     return res;
   }
   
   int graph_insert(string s)
   {
     string alpha = "";
     string beta = "";
     int flag = 0;
   
     //////////////////////splitting b/w alpha & beta/////////////////////////////////////////////////////////////////
     for(int i = 0; i < s.size(); i++)
     {
       if(s[i] != '-')
       {
	      if(flag == 0)
	       alpha += s[i];
	      else if(s[i]==';')
	       break;	   
	      else
	       beta+=s[i];
       }

       else
       {
	     if(s[++i] == '>')
	       flag++;
	    else
	      return -1;	
   	   }
     }
     
     if(flag != 1)
       return -1;
     
     cout << "alpha: " << alpha;
     cout << "\nbeta : " << beta << "\n"; 
    
     int j;
     for(int i = 0, j = 0; i < alpha.size() || j < beta.size(); i++, j++)
     {
       graph[alpha].insert(alpha[i]);
       
       if(j < beta.size())
       {
	     graph[alpha].insert(beta[j]);
       }
      }
      return 1;
   }
   
   /////////////////Adding elemets of alpha as well as beta into alpha's closure///////////////////////
   string closure(map<string,set<char> >::iterator mit)
   {
     string res = "";
     
     set<char>::iterator sit;
     set<char>::iterator s1it;
     map<string,set<char> >::iterator m2it;
     string temp,alpha,beta,sub_beta;
     int flag = 1;
     int old_size, new_size;
     
     while(flag)                             //While loop runs unitll there is no change in closure of all alpha's 
     {
	      flag = 0;
	      alpha = mit->first;
	      beta = "";
	      old_size = graph[alpha].size();
	
	       for(sit = mit->second.begin(); sit != mit->second.end(); sit++)
	          beta += *sit;	
	   
	   for(m2it = graph.begin(); m2it != graph.end(); m2it++)    
	   {
	      sub_beta = "";
	  
	      if(m2it != mit)
	         sub_beta = m2it->first;
	  
	      if(sub_beta.size() > beta.size())
	       continue;
	  
	     int beta_flag;
	  
	     for(int i = 0; i < sub_beta.size(); i++)
	     {
	         beta_flag = 0;
	      
	         for(int j = 0; j < beta.size(); j++)
		          if(beta[j] == sub_beta[i])
		            beta_flag = 1;
	        
	        if(beta_flag == 0)
		         break;
	     }
		 
		 if(beta_flag == 0)
	      continue;
	  
	     for(s1it = graph[sub_beta].begin(); s1it != graph[sub_beta].end(); s1it++)
	     {
	      graph[alpha].insert(*s1it);
	     }
	 }
	 
	   new_size = graph[alpha].size();
	 
	    if(old_size != new_size)
	       flag = 1;
   }
      
      string test = mit->first;
      
      for(int i = 0; i < test.size(); i++)
	      graph[test].erase(test[i]);  //erase's alpha elements from beta
      
      for(sit = mit->second.begin(); sit != mit->second.end(); sit++)
	      res += *sit;
      
      return res;
}

   ///////////////////////////////finding the complete closure of alpha//////////////////////////////////////////////////////
   void extraneous()
   {
     int extra_flag = 1;
     map<string,set<char> >::iterator eit;
    
     set<char>::iterator esit;
    
     while(extra_flag)
     {
      extra_flag = 0;
      
      for(eit = graph.begin(); eit != graph.end(); eit++)
      {
	       string extra = eit->first;
	      string test,test2;
	
	      if(extra.size() == 1)
	        continue;
	
	     for(int i = 0; i < extra.size(); i++) 
	     {
	         test = string_maker(extra,i)+"-";
	         
	         test2 = extra+"+";
	  
	         for(int j = 0; j < extra.size(); j++)
	         { 
				      if(extra[i] != extra[j])
	            {
	                graph[test].insert(extra[j]);
	                graph[test2].insert(extra[j]);
	            }
	           
	           else
	             graph[test2].insert(extra[j]);
	         }
	         
	         map<string,set<char> >::iterator temp_it;
	         
	         for(temp_it = graph.begin(); temp_it != graph.end(); temp_it++)
	             if(temp_it->first == test)
	               break;
	 
	        map<string,set<char> >::iterator temp_it2;
	  
	        for(temp_it2 = graph.begin(); temp_it2 != graph.end(); temp_it2++)
	            if(temp_it2->first == test2)
	              break;
	            
	            string temp1 = closure(temp_it2);
	            string temp2 = closure(temp_it);
	  
	           if(temp1 == temp2)
	           {
	             graph.erase(eit->first);
	           
	             test = string_maker(test, test.size()-1);
	    
	             for(esit = temp_it->second.begin(); esit != temp_it->second.end(); esit++)
	                  graph[test].insert(*esit);
	           
	            graph.erase(temp_it->first);
	            graph.erase(temp_it2->first);
	            
	            extra_flag = 1;
	            eit = graph.begin();
	            break;
	          }
	          
	          else
	          {
	             graph.erase(temp_it->first);
	             graph.erase(temp_it2->first);
	          }
	       }	
        } 
    }
  
     for(eit = graph.begin(); eit != graph.end(); eit++)
     {
       string temp = eit->first;
      
       for(int i = 0; i < temp.size(); i++)
	       graph[eit->first].erase(temp[i]);
    }
    
   }
   ////////////////////////////////////Printing the graph/////////////////////////////////////
    void print()
    {
      map<string,set<char> >::iterator mit;
      set<char>::iterator sit;
      
      for(mit = graph.begin(); mit != graph.end(); mit++)
      {
	     cout<<"\n"<<mit->first;
	     
	     for(sit = mit->second.begin(); sit != mit->second.end(); sit++)
	        cout<<" --> "<<*sit;
      }      
    }
};

/////////////////////////////////Main function/////////////////////////////////////////////////
int main()
{
  string s;
  Graph g;  
  int count = 1;
  int r;
  
  while(1)
  {
    cout << "functional dependency " << count++ << " ) ";
    cin >> s;
    
    if(s == "exit")
      break;  
    
    r = g.graph_insert(s);
    
    if(r < 0)
    {
      cout << "\nInvalid entry\n";
      count--;
    }
  }
  
  g.print();
  g.extraneous();
  g.print();
  
  return 0;
}
