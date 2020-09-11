//Saide J
//CS1428H Fall 2019

#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<vector>
#include<ctime>
#include<cstdlib>

using namespace std;


/* struct holds the rgb values of a pixel*/
struct pixels{
    float redColor;
    float greenColor;
    float blueColor;
};

/*struct holds the characteristics of a ppm file*/
struct images{
    string magicNumber;
    int thresholdVal;
    int cols, rows;
    //2d vector of struct pixel 
    //also helps with the location of the pixel
    vector<vector<pixels> > location;
    string fileName;     
};

/*this function takes in the fileName and checks the file extentsion
 * to see if it is in fact a ppm file.
 *
 * the function returns true if the file extention is ppm and returns
 * false if it doesn't. */
bool checkRightFile(char fileName[], string fileExtent = ".ppm"){
   //saves the size of the file extension
   int numSize = fileExtent.size();
   int fileName_length = strlen(fileName);
   //checks the last 4 characters of the file name to see if the extension
   //is ppm
   for (int i = fileName_length - numSize; i < fileName_length; i++){
	if ((fileName[i] == '.' && fileName[i+1] == 'p') && (fileName[i+2] == 'p' && fileName[i+3] == 'm'))
	   return true;
	else
	   return false;
   }
   return false;
}

/*this function takes in the ifstream and the cstring of the file name
 * and checks to see if the file exists and is open. It returns true if
 * the file exists and is open, and returns false if it doesn't
 * exist and is not open.*/
bool fileOpenSuccessful(ifstream& image, char fileName[]){
    image.open(fileName);
    if (!image.is_open()){
	cout << "Error 404: File Not Found" << endl;
	image.close();
	return false;
    }
    return true;
}

/*this function takes in ifstream and the struct type image in order
 * to store the  attributes of the ppm file, such as threshold value,
 * number of rows and columns, etc. The function also checks the magic
 * number to see if it is in fact a real ppm file.
 *
 * The function returns false if the file is not a real ppm file, and
 * return true if the saving of the certain attributes have been
 * completed.  */
bool loadDataSuccessful(ifstream& image, images& photo){
    bool isRight = false;
    while (!image.eof()){
	image >> photo.magicNumber;
	for (int i = 0; i < 2; i++){
	    //checks to see if the magic number is the correct one
	    if (photo.magicNumber[i] == 'P' && photo.magicNumber[i+1] == '3')
		isRight = true;
	}
	if (isRight){
	    image >> photo.cols;
	    image >> photo.rows;
	    image >> photo.thresholdVal;
	    
	    //resize the "outer" vector with number of rows
	    photo.location.resize(photo.rows);
	    for (int i = 0; i < photo.rows; i++){
		//resizes the "inner" vector with number of columns
		photo.location[i].resize(photo.cols);
	    }
	    //loads each individual pixels with their respective rgb values
	    for (int i = 0; i < photo.rows; i++){
		for (int j = 0; j < photo.cols; j++){
 	            image >> photo.location[i][j].redColor;
	            image >> photo.location[i][j].greenColor;
	            image >> photo.location[i][j].blueColor;
	        }
	    }
	    return true;
        }
	else{
	    cout << "Not the file type wanted. Will Exit The Loading Process" << endl;
	    return false;
	}
    return true;
    }
}

/* this function takes in the struct type image and set with default of editword, which tells what
 *  operation/changes have been done to to image itself, and cropRow and cropCol are for the crop
 *  image function. 
 *  
 *  The function renames the file with file extention and opens a file with that name. Then, it
 *  outputs all the information from struct type photo into the file and closes it.
 *
 *  Return type is void */
void createNewFile(images& photo, string editWord = "", int cropRow = 0, int cropCol = 0){
    ofstream newImage;
    string fileExtent = ".ppm";
    
    photo.fileName = photo.fileName + editWord;
    string newFileName = photo.fileName + fileExtent;
    cout << "Now Saving Your File As " << newFileName << endl;
     
    //function from the cstring library converts strings to cstring
    //the open function of ifstream only takes cstrings as arguments
    newImage.open(newFileName.c_str());
    newImage << photo.magicNumber << endl;
    newImage << photo.cols << " " << photo.rows << endl;
    newImage << photo.thresholdVal << endl;
 
    for (int i = cropRow; i < photo.location.size(); i++){
    	for (int j = cropCol; j < photo.location[i].size(); j++){
	    newImage << photo.location[i][j].redColor << endl;;
	    newImage << photo.location[i][j].greenColor << endl;
	    newImage << photo.location[i][j].blueColor << endl;;
	}
    }
    newImage.close();
    return;
}

/* this function takes in array of photos of struct type images and the size of the
 * array, and creates an html file by opening a ofstream  containing the created 
 * images with file extension of jpeg. 
 *
 * the return type is void */
void createHTML(images photo[], int numImages){
    ofstream html;
//    string fileExtent = ".html";
    string randImgExtent = ".jpeg";
    
    html.open("randomImages.html");
    html << "<!DOCTYPE html>" << endl;
    html << "<html>" << endl;
    html << "<head style=\"background-color:gray\">" << endl;
    html << "<body style=\"background-color:gray\">" << endl;
    html << "<title>Random Images</title>" << endl;
    html << "<h1>You Selected " << numImages << " Random Images</h1>" << endl;
    html << "<br>" << endl;
    html << "<ul>" << endl;
    
    //prints the links for the number of images chosen
    for (int i = 0; i < numImages; i++){
	html << "    <a href=\"" << photo[i].fileName << randImgExtent << "\" target=\"_blank\"</a>" << endl;
	html << "    <li>Random Image " << i+1 << "</li>" << endl;
	
    }
    html << "</u1>" << endl << endl;
    html << "</body>" << endl;
    html << "</html>" << endl;
    
    html.close();
    return;
    
}

/* this function takes in the saved values from the struct type images and changes
 * the rbg values to apply filters on to the photo. After the filters have been 
 * applied, a new file will be created through the createNewFile function.
 *
 * the return type is void */
void filterPhoto(images& photo){
    int choiceNum;
    bool wrongChoice = false;

    cout << "++++++++ Filter ++++++++++" << endl;
    do{
    cout << "Choose Your Filter From The List Below: " << endl;
    cout << "1. Red" << endl;
    cout << "2. Blue" << endl;
    cout << "3. Green" << endl;
    cout << "4. GrayScale" << endl;
    cout << "5. Sepia" << endl;
    cin >> choiceNum;
    cout << endl;
    
    switch (choiceNum){
	case 1:
	   cout << "You Have Chosen The Red Filter" << endl;
	   for (int i = 0; i < photo.rows; i++){
		for (int j = 0; j < photo.cols; j++){
		    photo.location[i][j].redColor = 0;
		}
	   }
	   wrongChoice = false;
	   createNewFile(photo, "_redFilter");
	   break;

	case 2:
	    cout << "You Have Chosen The Blue Filter" << endl;
	    for (int i = 0; i < photo.rows; i++){
		for (int j = 0; j < photo.cols; j++){
		    photo.location[i][j].blueColor = 0;
		}
	    }
	    wrongChoice = false;
	    createNewFile(photo, "_blueFilter");
	    break;

	case 3:
	    cout << "You Have Chosen The Green Filter" << endl;
	    for (int i = 0; i < photo.rows; i++){
		for (int j = 0; j < photo.cols; j++){
		    photo.location[i][j].greenColor = 0;
		}
	    }
	    wrongChoice = false;
	    createNewFile(photo, "_greenFilter");
	    break;

	case 4:
	    cout << "You Have Chosen The GrayScale Filter" << endl;
	    for (int i = 0; i < photo.rows; i++){
		for (int j = 0; j < photo.cols; j++){
		    photo.location[i][j].redColor = (photo.location[i][j].redColor * 0.3) + 
		    (photo.location[i][j].greenColor * 0.59) + (photo.location[i][j].blueColor * 0.11);

		    photo.location[i][j].greenColor = (photo.location[i][j].redColor * 0.3) + 
		    (photo.location[i][j].greenColor * 0.59) + (photo.location[i][j].blueColor * 0.11);

		    photo.location[i][j].blueColor = (photo.location[i][j].redColor * 0.3) + 
		    (photo.location[i][j].greenColor * 0.59) + (photo.location[i][j].blueColor * 0.11);
		}
	    }
	    wrongChoice = false;
	    createNewFile(photo, "_grayscaleFilter");
	    break;

	case 5:
	     cout << "You Have Chosen The Sepia Filter" << endl;
	     for (int i = 0; i < photo.rows; i++){
		for (int j = 0; j < photo.cols; j++){
		    photo.location[i][j].redColor = (photo.location[i][j].redColor * 0.439) + 
		    (photo.location[i][j].greenColor * 0.259) + (photo.location[i][j].blueColor * 0.078);

		    photo.location[i][j].greenColor = (photo.location[i][j].redColor * 0.439) + 
		    (photo.location[i][j].greenColor * 0.259) + (photo.location[i][j].blueColor * 0.078);

		    photo.location[i][j].blueColor = (photo.location[i][j].redColor * 0.439) + 
		    (photo.location[i][j].greenColor * 0.259) + (photo.location[i][j].blueColor * 0.078);
		}
	    }
	    wrongChoice = false;
	    createNewFile(photo, "_sepiaFilter");
	    break;

	default:
	    cout << "Incorrect Choice!" << endl;
	    wrongChoice = true;
    }
    //if a wrong choice is made, the user will be redirected to the menu
    }while(wrongChoice);
    return;
}

/* this function takes in the struct type images, which contains the values of the loaded ppm file
 * and crops the picture by row or by column. The user is prompted by how much they want to take
 * off from each side, and the program crops by their input. After the photo has been edited,
 * the createNewFile function is called.
 *
 * the return type is void */
void cropPhoto(images& photo){
    //FIXME: implent check for inputs less than 0
    //what happens if you take too much off
    int userChoice;
    bool wrongChoice = false;
    int top_rows, bottom_rows = 0;
    int left_cols, right_cols = 0;
    
    do{
         cout << "+++++++++ Crop Filter ++++++++++" << endl;
         cout << "Select an option: " << endl;
         cout << "1. Crop By Row" << endl;
         cout << "2. Crop By Column" << endl;
         cin >> userChoice;
         cout << endl;

         switch (userChoice){
	     case 1:
	    	wrongChoice = false; 	     

    	    	cout << "++++++++++++++ Crop By Row +++++++++++++++" << endl;
            	cout << "Enter The Amount of Rows You Would Like to Cut From The Top: ";
    	    	cin >> top_rows;
            	cout << endl << "Enter The Amount of Rows You Would Like to Cut From The Bottom: ";
            	cin >> bottom_rows;
	
	    	if (top_rows >= photo.rows || bottom_rows >= photo.rows || top_rows + bottom_rows >= photo.rows ){
		    cout << "Error: Cropping Too Many Rows" << endl;
		    wrongChoice = true;
		    break;
	  	}
	        
		if (top_rows < 0 || bottom_rows < 0){
		    cout << "Error: Negative Numbers Have Been Entered" << endl;
		    wrongChoice = true;
		    break;
		}

		//uses pop_back to remove the amount the user wanted from the bottom
	        //of the photo
    	        for (int i = 0; i < bottom_rows; i++){
        	    photo.location.pop_back();
    	        }
	
	        //uses size() to find amount rows present after removing the specified amount
	        //from the bottom rows. Then, takes that size and takes away amount removed
	        //the from top and saves to photo.rows
    	        photo.rows = photo.location.size() - top_rows; 
    	        createNewFile(photo, "_cropRow", top_rows);
	        break;

 	    case 2:
	    	wrongChoice = false;

    	    	cout << "++++++++++++ Crop By Column +++++++++++" << endl;
    	    	cout << "Enter The Amount Of Columns You Would Like to Cut From The Left: ";
    	    	cin >> left_cols;
    	    	cout << endl << "Enter The Amount Of Columns You Would Like to Cut From The Right: ";
    	    	cin >> right_cols;

		if (left_cols >= photo.cols || right_cols >= photo.cols || left_cols + right_cols >= photo.cols ){
		    cout << "Error: Cropping Too Many Rows" << endl;
		    wrongChoice = true;
		    break;
	    	}
	        
		if (left_cols < 0 || right_cols < 0){
		    cout << "Error: Negative Numbers Have Been Entered" << endl;
		    wrongChoice = true;
		    break;
		}

	        //goes through every row and takes off the amount of right columns 
	        //specified by the user
    	    	for (int i = 0; i < photo.rows; i++){
	            for (int j = 0; j < right_cols; j++){
	            	photo.location[i].pop_back();
	            }
    	        }
	
	    	//adjusts the number of cols
            	photo.cols = photo.cols - right_cols - left_cols;
	    	//sends the number of left cols as well, so the createNewFile function
	    	//knows where to start printing the image
	    	createNewFile(photo, "_cropCol", 0, left_cols); 	    
	    	break;

	    default:
	    	cout << "Incorrect Choice. Try Again" << endl;
	    	wrongChoice = true;
		
        }
        //if user makes a wrong choice, they are redirected back to the menu
    }while(wrongChoice);	

return;
}
    
/* this function takes in the struct type image and rotates the photo by 90 degrees
 * each time it is called.
 *
 * the return type is void. */
void rotatingPhoto(images& photo){
    images temp;
    //the following copies info from photo to the temp
    temp.magicNumber = photo.magicNumber;
    temp.thresholdVal = photo.thresholdVal;
    temp.cols = photo.rows;
    temp.rows = photo.cols;
   
    //changes the number of rows from number of columns in original photo
    temp.location.resize(photo.cols);
    for (int i = 0; i < photo.cols; i++){
	//changes the number of columns from number of rows in original photo
	temp.location[i].resize(photo.rows);
    }
    for (int i = 0; i < photo.rows; i++){
	for (int j = 0; j < photo.cols; j++){
	    //goes through changes each row from the original to the far right column
	    //in the new photo
	    temp.location[j][photo.rows - 1 - i] = photo.location[i][j];
	}
    }
    //saves the original file name to the temp struct
    temp.fileName = photo.fileName;
    //assigns the temp struct to the original struct
    photo = temp;
    return;
}

/* this function takes in the image struct and prompts user for the rotation they want
 * to have done to their photo. The function then calls the rotatingPhoto function
 * to rotate the image the appropriate amount of times to achieve what the user called
 * for. After the rotations are done, a new file is created by the function, create
 * -NewFile.
 *
 *  the return type is void */
void rotatePhoto(images& photo){
    images temp; //temporary variable for photo
    temp = photo;
    bool wrongChoice;
    int userInput;

    do{
    	cout << "++++++++ Rotate Menu +++++++" << endl;
    	cout << "1. 90 degrees clockwise" << endl;
    	cout << "2. 180 degrees" << endl;
    	cout << "3. 90 degrees counterclockwise" << endl;
    
    	cin >> userInput;
    	switch (userInput){
	    case 1:
		//90 degree rotation clockwise
		rotatingPhoto(photo);
	        wrongChoice = false;
		createNewFile(photo, "_rotate90");
		break;
	    case 2:
		//180 degree rotation clockwise
		for (int i = 0; i < 2; i++){
		    rotatingPhoto(photo);
		}
		wrongChoice = false;
		createNewFile(photo, "_rotate180");
		break;
	    case 3:
		//270 degree rotation clockwise
		for (int i = 0; i < 3; i++){
		    rotatingPhoto(photo);
		}
		wrongChoice = false;
		createNewFile(photo, "_rotate90counter");
		break;
	    default:
	    	cout << "Incorrect Choice! Try Again. " << endl;
	    	wrongChoice = true;
	    	break;
    	}
    }while(wrongChoice);
    return;
}

/* this function takes in an array of struct type of images and
 * string of numbers. The function creates 3 different images
 * and at the end assign names to fileNames in the array
 *
 * the return type is void */
void makeRandomImage(images randomImage[], string numOfImage){
    const int SET_NUM_IMAGES = 3;
    int numImages = 0;
    //the following helps produce random images
    //everytime the function is called
    int set0 = rand() % 255;
    int set1 = rand() % 155 + 100;
    int set2 = rand() % 255;
    int set3 = rand() % 3 - 1;
    int setRand = rand() % 5;
   
    //assigns the each index in the array with necessary attributes
    //for the ppm file
    for (int i = 0; i < SET_NUM_IMAGES; i++){
	randomImage[i].magicNumber = "P3";
        randomImage[i].cols = 300;
	randomImage[i].rows = 300;
	randomImage[i].thresholdVal = 255;
        randomImage[i].location.resize(randomImage[i].rows);
	    for (int j = 0; j < randomImage[i].rows; j++){
		randomImage[i].location[j].resize(randomImage[i].cols);
	    }
    } 
    //for randomImage[0] - static
    for (int i = 0; i < randomImage[0].rows; i++){
    	for (int j = 0; j < randomImage[0].cols; j++){
	    randomImage[0].location[i][j].redColor = rand() % 255;
	    randomImage[0].location[i][j].greenColor = rand() % 255;
	    randomImage[0].location[i][j].blueColor = rand() % 255;
	}
    }

    //for randomImage[1] - creates pattern ofvertical lines
    for (int i = 0; i < randomImage[1].rows; i++){
	int setRand2 = rand() % 255;
	for (int j = 0; j < randomImage[1].cols; j++){
	    randomImage[1].location[j][i].redColor = setRand2 - (set0 * set3);
	    randomImage[1].location[j][i].greenColor = setRand2 - (set1 * set3);
	    randomImage[1].location[j][i].blueColor = setRand2 - (set2 * set3);
	}
    }

    //for randomImage[2] - solid color
    for (int i = 0; i < randomImage[2].rows; i++){
	for (int j = 0; j < randomImage[2].cols; j++){
	    randomImage[2].location[i][j].redColor = set0 + (i*0.20 * set3);
	    randomImage[2].location[i][j].greenColor = set1 + (i*0.20 * set3);
	    randomImage[2].location[i][j].blueColor = set2 + (i*0.20 * set3);
	}
    }
    
    //assigns names to the files
    for (int i = 0; i < SET_NUM_IMAGES; i++){
	randomImage[i].fileName =  "randomImage";
	randomImage[i].fileName.push_back(numOfImage[i]);
    }
    cout << endl;
   return;

}

/* this function generates random images by calling the makeRandomImages function
 * for the certain number times the user specifies, as they enter how many random images
 * they want. 
 *
 * the function also takes the random Images and save them in an array, which is sent to
 * the createHTML function so that the files are in the html file.
 *
 * the return type is void */
void generateRandomImage(){
    int numImages = 0;
    const int SET_NUM_IMAGES = 3;
    images randomImage[SET_NUM_IMAGES];
    string numOfImage = "123";  //helps with naming files
    cout << "+++++++++ Generating Random Images ++++++++++++" << endl;
    cout << "Enter The Number Of Random Images: ";
    cin >> numImages;
    images randArray[numImages]; //the array for the html file

    for (int i = 0; i < numImages; i++){
	makeRandomImage(randomImage, numOfImage);
	int index = rand() % SET_NUM_IMAGES;
        string setNumIndex = '_' + numOfImage.substr(rand() % SET_NUM_IMAGES, (rand() % (SET_NUM_IMAGES - 1)) + 1);
	createNewFile(randomImage[index], setNumIndex);
        randArray[i] = randomImage[index];
    }
    createHTML(randArray, numImages);
    return;
} 

int main(){
    srand(time(0));
    ifstream image;
    images photo; 
    char userChoice; //this for the main menu
    char userChoice2; //this is for the manipulation menu
    bool wrongChoice;
    bool isOn = true;

    cout << "Welcome To The Mini PhotoShop App!" << endl << endl;
    
    while (isOn){
	//cstring is set as default to changes can be made to name later
        char fileName[] = "default.ppm";
	cout << endl;
        do{
            cout << "++++++++++ Main Menu +++++++++++" << endl;
            cout << "1. Manipulate Image [ m ]" << endl;
            cout << "2. Generate Image [ g ]" << endl;
            cout << "3. Quit [ q ]" << endl;

            cin >> userChoice;
            userChoice = tolower(userChoice);
            switch (userChoice){
	        case 'm':
	            cout << "Enter The Name Of the Image File You Would Like To Edit: ";
	    	    cin >> fileName;
			
		    //checks to see if the file is valid file for the program
	            if (checkRightFile(fileName) && fileOpenSuccessful(image, fileName)){
			//if the file meets all requirements, another check is implemented
			//within the loadDataSuccessful function
		    	if (loadDataSuccessful(image, photo)){
			    photo.fileName = fileName;
			    //the file extension is removed from the file name
			    photo.fileName = photo.fileName.substr(0, photo.fileName.find('.'));
		            cout << endl;

	       	    	    do{
	    	    	    	cout << "++++++ Manipulate Image Menu ++++++" << endl << endl;
	    	    	    	cout << "1. Filter [ s ]" << endl;
	    	    	    	cout << "2. Crop [ c ]" << endl;
	    	    	    	cout << "3. Rotate [ r ]" << endl;
	    	    	    	cout << "4. Quit [ q ]" << endl;
	    	    	    	cin >> userChoice2;
	    
	    	    	    	userChoice2 = tolower(userChoice2);
	   	    	    	switch (userChoice2){
			    	    case 's':
		    	    	        filterPhoto(photo);
		    	    	        wrongChoice = false;
		    	    	        break;
	  		    	    case 'c':
		    	    	        cropPhoto(photo);
		    	    	        wrongChoice = false;
		    	    	        break;
			    	    case 'r':
		    	    	        rotatePhoto(photo);
		    	    	        wrongChoice = false;
		    	    	        break;
			    	    case 'q':
		    	    	        wrongChoice = false;
			    	        image.close();
		    	    	        break;
			    	    default:
		    	    	    	cout << "Incorrect Choice! Try Again." << endl;
		    	    	    	wrongChoice = true;
		    	    	    	break;
	    	    	    	}
			    //if user makes wrong choice, they are redirected to this menu
	            	    }while(wrongChoice);
			    //this is set to false because choice has been made through the main menu
	            	    wrongChoice = false;
	            	}
			//if the loadDataSuccessful function returns false, the ifstream will close the file
			//and knock the user back to the main menu
		    	else{
		            image.close();
		            break;
		    	}
		    }
		    //if the file returns false for checkRightFile and fileOpenSuccessful, the ifstream will
		    //close the file and knock the user back to the main menu
		    else{
		        image.close();
		    	break;
		    }
		//this is the end of the manipulation menu
	        break;
	    	case 'g':
		    cout << endl;
	    	    cout << "You Are Being Directed To The Generate Random Image Menu" << endl << endl;
	     	    generateRandomImage();
	    	    wrongChoice = false;
	    	    break;
	    	case 'q':
	            wrongChoice = false;
		    //the q from the main menu, allows the user to exit the loop and end the program
	            isOn = false;
	            break;
	    	default:
	            cout << "Incorrect Choice! Try Again." << endl;
	            wrongChoice = true;
    	    }
	//main menu continues to loop if a wrong choice is made
        }while(wrongChoice);
    }
    //this the end of the while loop
    return 0;
}
