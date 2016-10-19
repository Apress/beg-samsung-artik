// --- Include the header file to use libcurl from your source code
//     or you will see compiler errors:
#include <curl/curl.h>

// --- Define a variable to act as a handle (or pointer) to reference
//     the curl entity.
//     Create another to store the result string when you send the
//     curl call to action.
   CURL *myCurlEntity;
   CURLcode myCurlResult;

// --- Initialise the curl entity
   myCurlEntity = curl_easy_init();

// --- Create a set of request headers
   struct curl_slist *requestHeader = NULL;

   char bearer[60]="";

   requestHeader = curl_slist_append(requestHeader,
                   "Content-Type: application/json");

   sprintf(bearer, "Authorization: Bearer %s", device_token);

   requestHeader = curl_slist_append(requestHeader, bearer);

// --- Create a request body to transmit to the remote system.
//     In this example, it is a SAMI transaction request
//     formatted with JSON data structures:

   char requestBody[256]="";

   sprintf(requestBody,"{\n
     \"sdid\": \"%s\",\n
     \"type\": \"message\",\n
     \"data\": {\n
           \"temperature\": %f                \n
      }\n
   }", device_id, temperature);

// --- Now configure the options on the curl entity to make it ready:
   curl_easy_setopt(myCurlEntity, CURLOPT_URL, samiUrl);
   curl_easy_setopt(myCurlEntity, CURLOPT_HTTPHEADER, requestHeader);
   curl_easy_setopt(myCurlEntity, CURLOPT_POSTFIELDS, requestBody);
   curl_easy_setopt(myCurlEntity, CURLOPT_VERBOSE, 1L);

// --- Make the call and capture the result:
   myCurlResult = curl_easy_perform(myCurlEntity);

// --- Handle an error if there was one:
   if (myCurlResult != CURLE_OK)
   {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
      curl_easy_strerror(myCurlResult));
   }

// --- Free up the memory allocated to the headers when they were created
//     and cleanup any other internal storage managed by the libcurl tools:
   curl_slist_free_all(requestHeader);

   curl_easy_cleanup(myCurlEntity);
