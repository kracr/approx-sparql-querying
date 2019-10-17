//
// Created by ahilya on 10/10/19.
//

#include <iostream>
#include <redland.h>

const unsigned char* load_file(char const* path);


int main(){
    librdf_world* world = librdf_new_world();
    librdf_storage* storage = librdf_new_storage(world, "hashes", "trial", "hash-type='memory'");
    librdf_model* model = librdf_new_model(world, storage, nullptr);
    librdf_parser* parser = librdf_new_parser(world, "", "text/turtle", nullptr);

    librdf_uri *baseUri = librdf_new_uri(world, (const unsigned char *)"."); //needed for dummy uri, doesn't create query otherwise.

    FILE *cfPtr = fopen("10000.n3", "r");
    if (cfPtr == nullptr){
        return -1;
    }
    -
    librdf_parser_parse_file_handle_into_model(parser, cfPtr, 1, baseUri, model);


    const unsigned char* query_string = load_file("query1.sparql");
    librdf_query* query = librdf_new_query(world, "sparql", nullptr, query_string, baseUri);
    librdf_query_results* results = librdf_query_execute(query, model);
    unsigned char* result_as_string = librdf_query_results_to_string(results, nullptr, baseUri);
    std::cout<<result_as_string;
    return 0;
}


const unsigned char* load_file(char const* path)
{
    char* buffer = 0;

    long length;
    FILE * f = fopen (path, "rb"); //was "rb"

    if (f)
    {
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = (char*)malloc ((length+1)*sizeof(char));
        if (buffer)
        {
            fread (buffer, sizeof(char), length, f);
        }
        fclose (f);
    }
    buffer[length] = '\0';

    const auto* return_buff = reinterpret_cast<const unsigned char*>(buffer);

    return return_buff;
}