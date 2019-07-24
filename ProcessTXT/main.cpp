// Used for file processing
#include <iostream>
#include <fstream>
// Used for String Processing
#include <string>
#include <sstream>
// Used for ShellExecute
#include <windows.h>

// Structures Used to Process Requests and Responses
struct httpRequest
	{
		std::string frame;
		std::string src_IP;
		std::string dst_IP;
		std::string getObject;
		std::string response_frame;
		std::string linked_flag;
	};
struct httpResponse
	{
		std::string frame;
		std::string src_IP;
		std::string dst_IP;
		std::string resCode;
		std::string conTyp;
		std::string conLen;
		std::string conEnc;
		std::string conComSize;
		std::string conUncomSize;
		std::string request_frame;
		std::string linked_obj;
		std::string linked_flag;
	};

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

// Function to remove undesired char from string


std::string remove_char(const std::string &input, char to_remove){
    std::string output;
    for(unsigned i=0; i<input.size(); ++i)
        if(input[i]!=to_remove)
            output+=input[i];
    return output;
}


// Function to process temporary file and write output to .CSV file
int tmp_file_to_csv (const std::string& input_file, const std::string& output_file)
	{
		std::string line;
		int i, j, req_flag=0;
		int req_count=0, res_count=0;
		std::string arr[20];
		
		// Create Arrays to save Request and response data
		httpRequest * point_req = new httpRequest[100];
		httpResponse * point_res = new httpResponse[100];
		
		// Open files for reading and writing
		std::ifstream in_file (input_file.c_str());
		std::cout << "Opening input file: " << input_file << "\n";
		if (!(in_file.is_open())) return 1;
		std::ofstream out_file (output_file.c_str());
		std::cout << "Opening output file: " << output_file << "\n";
		if (!(out_file.is_open())) return 1;
		
		// Starting File processing
		if (in_file.is_open())
			{
				i=0;
				
				// Read input file line by line
				while ( std::getline (in_file,line) )
					{
						
						// Clean Array before processing line
						i=0;
						while (i<20)
							{
								arr[i]=""; i++;
							}
						
						// Split line into array of words
						i=0;
						std::stringstream ssin(line);
						while (ssin.good() && i < 20)
							{
        						ssin >> arr[i];
        						// std::cout << i << ":" << arr[i] << "\n";
        						++i;
							}	// END OF Split line into array of words
						
						// Verify if new message started
						if (arr[4] == "HTTP")
							{
								// This is where new message started and old data should be saved
								if (req_flag == 1)
									{
										// Write to Request table next entry
										std::cout << "point_req[" << req_count << "].frame:" << point_req[req_count].frame << "_\n";
										std::cout << "point_req[" << req_count << "].src_IP " << point_req[req_count].src_IP << "\n";
										std::cout << "point_req[" << req_count << "].dst_IP " << point_req[req_count].dst_IP << "\n";
										std::cout << "point_req[" << req_count << "].getObject " << point_req[req_count].getObject << "\n";
										std::cout << "point_req[" << req_count << "].response_frame " << point_req[req_count].response_frame << "\n\n";
										point_req[req_count].linked_flag="false";
										req_count++;
									}	
								if (req_flag == 0)
									{
										// Write to Responce table next entry
										
										// Make data consistant for postprocessing
										if (point_res[res_count].conEnc == "") point_res[res_count].conEnc="none";
										if (point_res[res_count].conComSize == "") point_res[res_count].conComSize=point_res[res_count].conLen;
										if (point_res[res_count].conUncomSize == "") point_res[res_count].conUncomSize=point_res[res_count].conLen;
										if (point_res[res_count].conLen == "") point_res[res_count].conLen=point_res[res_count].conUncomSize;
										
										// Write to standards output
										std::cout << "point_res[" << res_count << "].frame         :" << point_res[res_count].frame << "\n";
										std::cout << "point_res[" << res_count << "].src_IP        :" << point_res[res_count].src_IP << "\n";
										std::cout << "point_res[" << res_count << "].dst_IP        :" << point_res[res_count].dst_IP << "\n";
										std::cout << "point_res[" << res_count << "].resCode       :" << point_res[res_count].resCode << "\n";
										std::cout << "point_res[" << res_count << "].conTyp        :" << point_res[res_count].conTyp << "\n";
										std::cout << "point_res[" << res_count << "].conLen        :" << point_res[res_count].conLen << "\n";
										std::cout << "point_res[" << res_count << "].conEnc        :" << point_res[res_count].conEnc << "\n";
										std::cout << "point_res[" << res_count << "].conComSize    :" << point_res[res_count].conComSize << "\n";
										std::cout << "point_res[" << res_count << "].conUncomSize  :" << point_res[res_count].conUncomSize << "\n";
										std::cout << "point_res[" << res_count << "].request_frame :" << point_res[res_count].request_frame << "\n\n";
										point_res[res_count].linked_flag="false";
										res_count++;
									}								
								// Reset Request/Response indication
								req_flag=0; 
								// Set Request/Resonse Flags
								if (arr[6] == "GET") req_flag=1;
							} // END OF Verify if new message started
							
							// Getting Request data
							if (req_flag == 1)
								{
									if (arr[4] == "HTTP")
										{
											arr[0]=remove_char(arr[0], ' ');
											point_req[req_count].frame=arr[0];
											point_req[req_count].src_IP=arr[2];
											point_req[req_count].dst_IP=arr[3];
											point_req[req_count].getObject=arr[7];
											point_req[req_count].response_frame="Not Found ";
										}
										if ( line.find("Response in frame:") != std::string::npos )
											{
												arr[3] = arr[3].substr(0, arr[3].size()-1);
												point_req[req_count].response_frame=arr[3];												
											}
								}   // END OF Getting Request data
							
							// Getting Response data
							if (req_flag == 0)
								{
									if (arr[4] == "HTTP")
										{
											arr[0]=remove_char(arr[0], ' ');
											point_res[res_count].frame=arr[0];
											point_res[res_count].src_IP=arr[2];
											point_res[res_count].dst_IP=arr[3];
											point_res[res_count].resCode=arr[6] + " " + arr[7] + " " + arr[8] + " " + arr[9] + " " + arr[10] + " " + arr[11] + " " + arr[12] + " " + arr[13] + " " + arr[14] + " " + arr[15];
											point_res[res_count].request_frame="Not Found ";
										}
									if ( line.find("Content-Type:") != std::string::npos )
										{
											point_res[res_count].conTyp=arr[1] + " " + arr[2] + " " + arr[3] + " " + arr[4];												
										}
									if ( line.find("Content-Length:") != std::string::npos )
										{
											arr[1] = arr[1].substr(0, arr[1].size()-4);
											point_res[res_count].conLen=arr[1];												
										}
									if ( line.find("Content-encoded entity body") != std::string::npos )
										{
											arr[3] = arr[3].substr(1, arr[3].size()-3);
											point_res[res_count].conEnc=arr[3];	
											point_res[res_count].conComSize=arr[4];
											point_res[res_count].conUncomSize=arr[7];											
										}
									if ( line.find("Request in frame:") != std::string::npos )
										{
											arr[3] = arr[3].substr(0, arr[3].size()-1);
											point_res[res_count].request_frame=arr[3];												
										}
								}    // END OF Getting Response data

					} // END OF Read input file line by line
				// Postprocessing Data
				i=1;
				out_file << "Response in frame" << "," << "Server IP" << "," << "Client IP" << "," << "Result Code" << "," << "Content Type" << "," << "Content Length" << "," << "Compression" << "," << "Content Compressed Size" << "," << "Content Uncompressed Size" << "," << "Request in Frame" << "," << "Object Name" << "\n";
				// Process response by response
				while (i<=res_count)
					{
						std::string match_obj="";
						j=0;
						while (j<=req_count)
							{
								if (point_res[i].request_frame == "") 
									{
										point_res[i].linked_obj="<not linked>";
										break;
									}
								if (point_res[i].request_frame == point_req[j].frame)
									{
										match_obj=point_req[j].getObject;
									}
								j++;
							}
						out_file << point_res[i].frame << "," << point_res[i].src_IP << "," << point_res[i].dst_IP << "," << point_res[i].resCode << "," << point_res[i].conTyp << "," << point_res[i].conLen << "," << point_res[i].conEnc << "," << point_res[i].conComSize << "," << point_res[i].conUncomSize << "," << point_res[i].request_frame << "," << match_obj << "\n";
						i++;
					}
			}

		// Close files used for reading and writting
		in_file.close();
		out_file.close();
		return 0;
	}

/////////////////////////////////////////////
//          MAIN Function                  //
/////////////////////////////////////////////

int main(int argc, char** argv) {
// main function begins gere

	// Get Filename of the file for processing block
	std::string file_name="", cmd_string="";
	std::cout << "Enter file name which you would like to process:\n";
	
	// Workarround so that last HTTP Meaasge gets processed!!!
	std::getline(std::cin, file_name);
	cmd_string+="/C echo ";
	cmd_string+='"';
	cmd_string+="    dummy 	 dummy	dummy	HTTP "; 
	cmd_string+='"';
	cmd_string+='>';
	cmd_string+='>';
	cmd_string+=" ";
	cmd_string+=file_name;
	ShellExecute(0, "open", "cmd.exe", cmd_string.c_str(), 0, SW_HIDE);
	// End of Workarround
	
	std::cout << "You entered:   " << file_name << "\n";
	std::cout << "==========================================================\n";

	// Process Temp Line and create CSV
	std::string csv_out_file;
	csv_out_file=file_name + ".csv";
	if ( tmp_file_to_csv(file_name.c_str(), csv_out_file.c_str()) == 1 ) return 1;
	
	std::cout << cmd_string;
// This is end of Main function
return 0;
}


