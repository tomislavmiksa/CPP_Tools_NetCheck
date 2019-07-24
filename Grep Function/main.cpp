// Used for file processing
#include <iostream>
#include <fstream>
// Used for String Processing
#include <string>

// Functions to be used in main function

// Function to check if pattern is found in line
int grep(const std::string& input_line)
	{
		std::string pattern1="HTTP/1.1";
		std::string pattern2="[Response in frame:";
		std::string pattern3="Content-Type:";
		std::string pattern4="Content-encoded entity body";
		std::string pattern5="Content-Length";
		if (input_line.find(pattern1) != std::string::npos) 
			{
    			return 1;
			}
		if (input_line.find(pattern2) != std::string::npos) 
			{
    			return 1;
			}
		if (input_line.find(pattern3) != std::string::npos) 
			{
    			return 1;
			}
		if (input_line.find(pattern4) != std::string::npos) 
			{
    			return 1;
			}
		if (input_line.find(pattern5) != std::string::npos) 
			{
    			return 1;
			}
		return 0;
	}

/////////////////////////////////////////////
//          MAIN Function                  //
/////////////////////////////////////////////

int main(int argc, char** argv) {
// main function begins gere

	// Get Filename of the file for processing block
	std::string file_name="";
	std::cout << "Enter file name which you would like to process:";
	std::getline(std::cin, file_name);
	std::cout << "You entered:   " << file_name << "\n";
	std::cout << "==========================================================";
	
	// Open input file line by line block
	std::string line;
	std::string tmp_out_file;
	int grep_chk=0;
	tmp_out_file=file_name + ".tmp";
	std::ifstream orig_in_file (file_name.c_str());
	std::ofstream temp_out_file (tmp_out_file.c_str());
	if (orig_in_file.is_open())
		{
			while ( std::getline (orig_in_file,line) )
				{
					// Verify Line contains Pattern we are looking for and write it to temporary file
					if ( grep(line.c_str()) == 1 )
						{
							temp_out_file << line << "\n";
						}
				}
			orig_in_file.close();
			temp_out_file.close();
		}
	
// This is e4nd of Main function
return 0;
}


