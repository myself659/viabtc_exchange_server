#include <jansson.h>
#include <string.h>


static void run_tests()
{
    json_t *json;
    json_error_t error;
    const char str[] = "{\"array\":[80, \"A\", {\"B\": \"C\"}, 1, 2]}";
    size_t len = strlen(str) - strlen("garbage");

    json = json_loadb(str, len, 0, &error);
    if(!json) {
        printf("json_loadb failed on a valid JSON buffer");
    }
    json_decref(json);

	int user_id = json_integer_value(json_array_get(json, 0));
	printf("user_id=%d", user_id);
}

void main(void){
	run_tests()

}

