 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <time.h>
   
  //function to check if the input is correct
  //Pieces will be '0' '1' '2' '3' '4' '5' '6' '7' and 4 pieces
  int check_input(char input[]){
      int val=atoi(input);   //char to integer
      if( val==0 && (input[0]!=0)){ //if input was not numbers
          return 1;
      }else{
          int digit=0;
          int out_of_range=0;
          for(int i=0; i<4; i++){ //checking if input contains 8 or 9
              digit=val%10;
              val=val/10;
              if(digit==9 || digit==8){
                  out_of_range++;
                  break; 
               }
          }   
          return out_of_range; //return result, if contains return>0
      }
  }
   
 
  //function to calculate length of input
  int len(char input[]){
      int a=0;
      while(input[a]!='\n'){ //till it reaches enter button\end of input
          a++;
      }
      return a;
  }
  
 
  //function to read and save input
  void read_input(char input[]){
      read(0, input, 5); 
      input[5]='\0';
  }
 
 //check whether input is the same as secret code 
 //count misplaced and well placed pieces
 int check_places(char secret_code[], char input[]){
             int wellplaced=0, misplaced=0, input_left_size=0, secret_left_size=0;
             char input_left[4], secret_left[4];
             
             //just find all wellspaced
             for (int i=0; i<4; i++){ 
                 if(secret_code[i]==input[i]){    
                 wellplaced++;
                 }
                 else{     // if it's not wellplaced, we want to throw the values in temp arrays
                     input_left[input_left_size++] = input[i];
                     secret_left[secret_left_size++] = secret_code[i];
                 }
             }
             
             //by using temp arrays and comparing them we get misplaced ones
             for (int i=0; i<input_left_size; i++){ 
                 for (int j=0; j<secret_left_size; j++){
                     if(secret_left[i]==input_left[j]){
                         misplaced++; secret_left_size--;
                         secret_left[j]=secret_left[secret_left_size];
                         break;
                      }
                  }
             }
             
             //show the results to the user
             if(wellplaced==4){  
                 printf("Congratz! You did it!\n");    
                 return 0;
             }else{
                 printf("Wellplaced pieces: %d\n", wellplaced);
                 printf("Misplaced pieces: %d\n", misplaced);
                 return 0;
             }
   }
  
  
   int main(int ac, char** av){
       char secret_code[5]; //create varibale that saves secret code value
       
       //if the person is entered secret code, av[1] is secret code
       if(ac>2 && av[1][0] == '-' && av[1][1]=='c'){
           for(int i=0; i<4; i++){
               secret_code[i]=av[2][i]; 
           }
       }//if nothing was entered, random code will be generated
       else{  
           srand(time(NULL));
           
           for(int i = 0 ; i < 4 ; i++ ) {
               int random_number = (rand() % 8); 
               secret_code[i]=(random_number+'0'); //to transfer integer to char 
           }
      }
      
      secret_code[4]='\0';    //end of the string
      printf("Will you find the secret code?\n");
      
      for(int attempt=0; attempt<10; attempt++){
            printf("Round %d\n", attempt);
            
            char input[6]={0}; //read from standard input by calling read() function
            read_input(input);
            
            while (len(input)!=4 || check_input(input)!=0){ //while input is incorrect, notify an user and ask new input
                printf("Wrong input!\n");
                read_input(input);} //ask and read an input
                check_places(secret_code, input);
            }
      return 0; 
}
