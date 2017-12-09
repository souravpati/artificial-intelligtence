#include<bits/stdc++.h>
using namespace std;

int nq,ns;
vector<string> queries;
vector<string> sentence;
vector<vector<string>> kb;
unordered_map<string,string> theeta;
queue<string> que;
unordered_set<string> visited;
int found=0, iteration=0, countchar=0;




void standardization(){
	vector<string> wor;
	

	for(int i=0;i<ns;i++){
		string sub = to_string(i);
		
		for(int j=0;j<sentence[i].length();j++){
			if(sentence[i][j]==' ')sentence[i].erase(sentence[i].begin()+j);
			if(sentence[i][j]=='(' || sentence[i][j]==','){
				
				j++;
				
				if(sentence[i][j]>=97 && sentence[i][j]<=122){
					
					sentence[i].insert(j+1,sub);
				}
			}
		}
		sentence[i] = sentence[i]+'|';
		wor.clear();
		size_t pos = 0, next=0;
		string token;
		while ((next = sentence[i].find("|",pos)) != string::npos) {
    		token = sentence[i].substr(pos, next-pos);
    		pos = next+1;
    	
    		wor.push_back(token);
    		//cout<<token<<"\n";
    	
    	}
    	kb.push_back(wor);
	}
}

vector<string> comma(string s){
	//cout<<5;
	s+=",";
	size_t pos = 0, next=0;
	string token;
	vector<string> words;
	
	while ((next = s.find(",",pos)) != string::npos) {
    	token = s.substr(pos, next-pos);
    	pos = next+1;
    	
    	words.push_back(token);
    	//cout<<token<<"\n";
    	
    }
    return words;
}

bool unifyvar(vector<string> &arg1,vector<string> arg2){
	
	//cout<<4;
	for(int m =0;m<arg1.size();m++){
		if(arg1[m][0]>=65 && arg1[m][0]<=90){
			if(arg2[m][0]>=65 && arg2[m][0]<=90){
				if(arg1[m].compare(arg2[m])!=0) return false;
			}
			else if(theeta.find(arg2[m])!=theeta.end() && theeta[arg2[m]].compare(arg1[m])!=0) return false;
			else theeta[arg2[m]] = arg1[m];
		}
		else if(arg2[m][0]>=65 && arg2[m][0]<=90){
			if(theeta.find(arg1[m])!=theeta.end() && theeta[arg1[m]].compare(arg2[m])!=0) return false;
			else theeta[arg1[m]] = arg2[m];
		}
		else{
			if(theeta.find(arg1[m])!=theeta.end() && theeta.find(arg2[m])==theeta.end()) theeta[arg2[m]]=theeta[arg1[m]];
			if(theeta.find(arg1[m])==theeta.end() && theeta.find(arg2[m])!=theeta.end()) theeta[arg1[m]]=theeta[arg2[m]];
			//else return false;
		}
	}
	return true;


}

void unify2(vector<string> &a, vector<string> &b,int start, int &flag){
	



	//cout<<3;
	size_t pos1 = 0, pos2 = 0, pos3=0;
	vector<string> arg1;
	vector<string> arg2;
	int f;
	theeta.clear();
	for(int i=start;i<a.size();i++){
		f=0;
		pos1 = a[i].find("(");
		string p1 = a[i].substr(0,pos1);
		if(p1[0]=='~')
			p1.erase(p1.begin());
		else p1.insert(0,"~");
		for(int j=0;j<b.size();j++){
			pos2 = b[j].find("(");
			string p2 = b[j].substr(0,pos2);
			if(p1.compare(p2)==0){
				//unify2(a,b,i+1,0);
				arg1.clear();
				arg2.clear();
				pos3 = a[i].find(")");
				arg1 = comma(a[i].substr(pos1+1,pos3-pos1-1));
				pos3 = b[j].find(")");
				arg2 = comma(b[j].substr(pos2+1,pos3-pos2-1));
				bool possible = unifyvar(arg1,arg2);
				if(possible){
					f=1;
					b.erase(b.begin()+j);
					j--;
					flag=1;
				}	
			}
			
		}
		if(f==1) {a.erase(a.begin()+i);i--;}
	}
	string s="";
	if(flag==1){
		for(int i=0;i<a.size();i++){
			pos1 = a[i].find("(");
			string p1 = a[i].substr(0,pos1);
			s+=p1+"(";
			arg1.clear();
			pos3 = a[i].find(")");
			arg1 = comma(a[i].substr(pos1+1,pos3-pos1-1));
			for(int m =0;m<arg1.size();m++){
				if(theeta.find(arg1[m])==theeta.end()) s+=arg1[m];
				else s+=theeta[arg1[m]];
				if(m==arg1.size()-1) s+=")|";
				else s+=",";
			}
			
		}
		for(int i=0;i<b.size();i++){
			pos1 = b[i].find("(");
			string p1 = b[i].substr(0,pos1);
			s+=p1+"(";
			arg1.clear();
			pos3 = b[i].find(")");
			arg1 = comma(b[i].substr(pos1+1,pos3-pos1-1));
			for(int m =0;m<arg1.size();m++){
				if(theeta.find(arg1[m])==theeta.end()) s+=arg1[m];
				else s+=theeta[arg1[m]];
				if(m==arg1.size()-1) s+=")|";
				else s+=",";
			}
			
		}
		//cout<<s<<"\n";
		if(s=="") found=1;
		if(iteration>5000 || countchar>1000000) found=2;
		if(visited.find(s)==visited.end()) {
			visited.insert(s);
			que.push(s);
			iteration++;
			countchar += s.length();
		}
	}
}

bool unify(vector<string> a, vector<string> b){
	//cout<<2;
	int flag=0;
	unify2(a, b,0,flag);
	return flag==0?false:true;
}



void resolution(string q){
	//cout<<1;
	size_t pos = 0, next=0, p=0;
	string token;
	vector<string> words;
	
	while ((next = q.find("|",pos)) != string::npos) {
    	token = q.substr(pos, next-pos);
    	pos = next+1;
    	
    	words.push_back(token);
    	//cout<<token<<"\n";
    	
    }
    //cout<<words.size()<<"\n";

    for(int i=0;i<words.size();i++){
  //   	if(words[i][0]=='~')
		// 	words[i].erase(words[i].begin());
		// else words[i].insert(0,"~");
    	pos = words[i].find("(");
    	string predicate = words[i].substr(0,pos);
    	if(predicate[0]=='~')predicate.erase(predicate.begin());
    	
    	for(int j=0;j<=ns;j++){
    		if((pos= sentence[j].find(predicate))!=string::npos){
    			bool uni = unify(words,kb[j]);
    			if(found>0) return;
    			if(uni==false) continue;
    			
    			
    			
    			
    		}
    	}
  //   	if(words[i][0]=='~')
		// 	words[i].erase(words[i].begin());
		// else words[i].insert(0,"~");
    }

}



int main(){
	freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
	cin>>nq;
	queries.resize(nq);

	for(int i=0;i<nq;i++)
		cin>>queries[i];
	cin>>ns;
	sentence.resize(ns);
	string bogus;
	getline(cin,bogus);
	for(int i=0;i<ns;i++)
		getline(cin,sentence[i]);
	standardization();
	// for(int i=0;i<=ns;i++)
	// 	cout<<sentence[i]<<"\n";

	vector<string> wor;
	for(int i=0;i<nq;i++){
		theeta.clear();
		if(queries[i][0]=='~')
			queries[i].erase(queries[i].begin());
		else queries[i].insert(0,"~");
		wor.clear();


		while(!que.empty()) que.pop();
		visited.clear();
		
		wor.push_back(queries[i]);
		kb.push_back(wor);
		sentence.push_back(queries[i]);
		que.push(queries[i]+"|");
		found = 0;
		iteration = 0;
		countchar = 0;
		// queue<int> empty;
		// std::swap( que, empty );
		
		while(!que.empty()){
			if(found==2 || found ==1) break;
			string pass = que.front();
			que.pop();
			resolution(pass);
		}
		if(found == 1) cout<<"TRUE\n";
		else cout<<"FALSE\n";
		//resolution(queries[i]+"|");
		kb.pop_back();
		sentence.pop_back();
	}

	
	return 0;
}