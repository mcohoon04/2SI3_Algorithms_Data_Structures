#include "HugeInteger.h"

HugeInteger::HugeInteger(const std::string& val) {
	//create counter variable to iterate through string
	int i;
	string temp = val;

	//Check for empty string input
	if(temp.size()==0){
		throw std::invalid_argument("Empty string provided.");
	}
	//remove leading zeros
	temp=temp.erase(0, min(temp.find_first_not_of('0'), temp.size()-1));
	//cout<<"temp str:"<<temp<<"\n";
	//use conditional statement to test if minus sign in front of integer and adjust accordingly
	if(temp[0]=='-'){
	    this->isNeg = true;
		//check if character is an integer and throw exception if not
		if(temp[1]-'0'>=0 && temp[1]-'0'<=9){
		    	HI.push_back(-1*(temp[1]-'0'));
			    i=2;
		    }
		else{
			throw std::invalid_argument("only integer values are allowed.");
		}
	}
	else{
			//initialize counter variable i
	        i=0;
	        this->isNeg=false;
	}
	//Use while loop to iterate through the string and add characters to vector one at a time
	while(i<temp.size()){
		//check if character is an integer and throw exception if not
		if(temp[i]-'0'>=0 && temp[i]-'0'<=9){
			HI.push_back(temp[i]-'0');//change character to int by subtracting '0' or ASCII 48 and add to end of vector
		}
		else{
			throw std::invalid_argument("only integer values are allowed.");
		}
		i++;
	}
	//cout<<this->toString();
}

HugeInteger::HugeInteger(int n) {
	//a number n digits long is a number in the range 10^(n-1) to (10^n)-1
	if(n>=1){
		//provide a seed value
		srand(time(NULL));

		//set first digit to ensure it is not equal to 0
		HI.push_back(1+rand()%9);

		//utilize for loop to add n random integers between 0-9 to vector HI
		for(int i=1;i<n;i++){
			HI.push_back(rand()%10);//add random integer to end of vector HI
		}
		this->isNeg=false;
	}
	else{
		throw std::invalid_argument("n must be greater than or equal to 1.");
	}

}

HugeInteger HugeInteger::add(const HugeInteger& h) {
	int carry=0;
	int min_dig = min(h.HI.size(), HI.size());
	int max_dig = max(h.HI.size(), HI.size());
	int diff = max_dig-min_dig;
	string ans;
	//reverse the string ans
	string rev_ans;
	HugeInteger temp1 = HugeInteger(this->toString());
	HugeInteger temp2 = h;

	if(this->isNeg==true && h.isNeg==false){
	    temp1.HI[0]=temp1.HI[0]*-1;
	    temp1.isNeg=false;
	    return temp2.subtract(temp1);
	}

	else if(this->isNeg==false && h.isNeg==true){
	    temp2.HI[0]=temp2.HI[0]*-1;
	    temp2.isNeg=false;
	    return this->subtract(temp2);
	}

	else if(this->isNeg==true && h.isNeg==true){
	    temp1.HI[0]=temp1.HI[0]*-1;
	    temp2.HI[0]=temp2.HI[0]*-1;
	    rev_ans.append("-");
	}

    int i = temp2.HI.size()-1;
    int z = temp1.HI.size()-1;
    while(min_dig>0){
        int sum = temp2.HI[i]+temp1.HI[z]+carry;
        carry=sum/10;
		ans.append(to_string(sum%10));
        i--;
        z--;
        min_dig--;
    }

	if(temp1.HI.size()>temp2.HI.size()){
		for(int j=diff-1;j>=0;j--){
				int sum = temp1.HI[j]+carry;
				carry=sum/10;
				ans.append(to_string(sum%10));
			}
	}
	if(temp1.HI.size()<temp2.HI.size()){
		for(int k=diff-1;k>=0;k--){
				int sum = temp2.HI[k]+carry;
				carry=sum/10;
				ans.append(to_string(sum%10));
			}
	}

	while(carry){
		ans.append(to_string(carry%10));
		carry = carry/10;
	}


	for(int value=ans.size()-1;value>=0;value--){
		rev_ans.push_back(ans[value]);
	}

	return HugeInteger(rev_ans);
}

HugeInteger HugeInteger::subtract(const HugeInteger& h) {
		int min_dig = min(h.HI.size(), HI.size());
		int max_dig = max(h.HI.size(), HI.size());
		int diff = max_dig-min_dig;
		string ans;
		//reverse the string ans, which will be the final answer
	    string rev_ans;

	    HugeInteger temp1 = HugeInteger(this->toString());
	    HugeInteger temp2 = h;

	if(this->isNeg==true && h.isNeg==false){
	    temp1.HI[0]=temp1.HI[0]*-1;
	    temp1.isNeg=false;
	    temp1 = temp1.add(h);
	    temp1.HI[0]=temp1.HI[0]*-1;
	    return temp1;
	}

	else if(this->isNeg==false && h.isNeg==true){
	    temp2.HI[0]=temp2.HI[0]*-1;
	    temp2.isNeg=false;
	    return this->add(temp2);
	}

	else if(this->isNeg==true && h.isNeg==true){
	    temp1.HI[0]=temp1.HI[0]*-1;
	    temp1.isNeg=false;
	    temp2.HI[0]=temp2.HI[0]*-1;
	    temp2.isNeg=false;
	    return temp2.subtract(temp1);
	}

    if(this->compareTo(h)==-1){
        temp2=*this;
        temp1=h;
        rev_ans.append("-");
    }

	int i = temp2.HI.size()-1;
	int z = temp1.HI.size()-1;

	//main subtraction block
	while(min_dig>0){
	        //handles the need for borrowing
	    	if(temp1.HI[z]<temp2.HI[i]){
	    	    //initialize counter variable to interate through temp1 starting at the place after the current index
	    	    int count=z-1;
	    		temp1.HI[z]=temp1.HI[z]+10;
	    		while(temp1.HI[count]==0){
	    			count--;
	    		}
	    		temp1.HI[count]--;
	    		while(temp1.HI[count+1]==0){
	    		    //cout<<"val before:"<<temp1.HI[count+1];
	    			temp1.HI[count+1]=9;
	    			count++;
	    			//cout<<"val after:"<<temp1.HI[count+1];
	    		}
	    	}

	        int sub = temp1.HI[z]-temp2.HI[i];
	        ans.append(to_string(sub));
	        i--;
	        z--;
	        min_dig--;
	    }

	    if(temp1.HI.size()>temp2.HI.size()){
	    		for(int j=diff-1;j>=0;j--){
	    				ans.append(to_string(temp1.HI[j]));
	    			}
	    	}

	    if(temp1.HI.size()<temp2.HI.size()){
	    		for(int k=diff-1;k>=0;k--){
	    				ans.append(to_string(temp2.HI[k]));
	    			}
	    		ans.append("-");
	    	}

	    for(int value=ans.size()-1;value>=0;value--){
	    	rev_ans.push_back(ans[value]);
	    }

	    //remove leading zeros after a negative sign
	    //leading zeros without a negative sign are accounted
	    //for in the constructor
	    if (rev_ans[0] == '-') {
		    rev_ans.erase(0,1);
		    rev_ans.erase(0, rev_ans.find_first_not_of('0'));
		    rev_ans.insert(0,1,'-');
	    }
        //cout<<rev_ans<<"\n";
	    return HugeInteger(rev_ans);
}

HugeInteger HugeInteger::multiply(const HugeInteger& h) {
    //create HI temps to be copys of operands so orignals are not affected
    HugeInteger temp1 = HugeInteger(this->toString());
	HugeInteger temp2 = h;

    //initialize variables to represent the size of operands and indexs
    int size1 = temp1.HI.size();
    int size2 = temp2.HI.size();
    int index1 = 0;
    int index2 = 0;

    //create vector to hold answer in reverse and string to hold final answer
	vector<int> ans(size1+size2,0);
	string final_ans="";

	//check if multiplying by zero
	if(temp1.HI[0]==0 || temp2.HI[0]==0){
	    return HugeInteger("0");
	}

	//If statement that checks if result is negative
	if ((this->isNeg == true && h.isNeg == false)) {
	    temp1.HI[0]=temp1.HI[0]*-1;
		final_ans.append("-");
	}
	else if(this->isNeg == false && h.isNeg == true){
	    temp2.HI[0]=temp2.HI[0]*-1;
		final_ans.append("-");
	}

	else if(this->isNeg == true && h.isNeg == true){
	    temp1.HI[0]=temp1.HI[0]*-1;
	    temp2.HI[0]=temp2.HI[0]*-1;
	}

	//Main multiplication loop
	//Iterate through temp1 from start to finish multiplying each digit in temp2
	//set ans at index of (index1+index2) to the sum of current product + carry + current value at that index
	//This result may be higher than 9, therefore a carry and an adjustment via modular division is needed like in addition
	for(int i=size1-1;i>=0;i--){
	    //initialize carry variable
	    int carry = 0;
	    //set index 2 back to 0
	    index2=0;
	    //Inner loop for iterating through temp 2 and doing the described multiplaction above
	    for(int k=size2-1;k>=0;k--){
	        int mult = ans[index1+index2]+carry+temp1.HI[i]*temp2.HI[k];
	        carry=mult/10;
	        ans[index1+index2]=mult%10;
	        index2++;
	    }
	    //if carry still left over add it to next index before restarting
	    if(carry>0){
	        ans[index1+index2]=ans[index1+index2]+carry;
	    }
	    //increment index1 for next iteration of algorithmn
	    index1++;
	}

	for(int value=ans.size()-1;value>=0;value--){
	    final_ans.append(to_string(ans[value]));
	    }

	    //remove leading zeros after a negative sign
	    //leading zeros without a negative sign are accounted
	    //for in the constructor
	if (final_ans[0] == '-') {
        final_ans.erase(0,1);
		final_ans.erase(0, final_ans.find_first_not_of('0'));
		final_ans.insert(0,1,'-');
	    }

	return HugeInteger(final_ans);
}

int HugeInteger::compareTo(const HugeInteger& h) {
    //flag to check if they are equal
    int flag = 0;
    int len1 = HI.size();
    int len2 = h.HI.size();

	if(this->isNeg==false && h.isNeg==true){
	    return 1;
	}
	else if(this->isNeg==true && h.isNeg==false){
	    return -1;
	}
	else if(this->isNeg==false && h.isNeg==false){
	    if(len1>len2){
	        return 1;
	    }
	    else if(len2>len1){
	        return -1;
	    }
	    else{
	        for(int i=0;i<len1;i++){
	            if(HI[i]>h.HI[i]){
	                flag=1;
	                return 1;
	            }
	            else if(HI[i]<h.HI[i]){
	                flag=1;
	                return -1;
	            }
	        }
	    }
	}
	else if(this->isNeg==true && h.isNeg==true){
	     if(len1>len2){
	        return -1;
	    }
	    else if(len2>len1){
	        return 1;
	    }
	    else{
	        if(HI[0]>h.HI[0]){
	            return 1;
	        }
	        else if(HI[0]<h.HI[0]){
	            return -1;
	        }
	        for(int i=1;i<len1;i++){
	            if(HI[i]>h.HI[i]){
	                flag=1;
	                return -1;
	            }
	            else if(HI[i]<h.HI[i]){
	                flag=1;
	                return 1;
	            }
	        }
	    }
	}
	if(flag==0){
	    return 0;
	}
	return 0;
}

std::string HugeInteger::toString() {
	string HugeInt;
	for(auto i : HI){
		HugeInt.append(to_string(i));
	}
	return HugeInt;
}
