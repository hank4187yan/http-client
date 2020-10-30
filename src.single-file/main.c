#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "http.h"


char *joinString(char *s1, char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1);//+1 for the zero-terminator
    if (result == NULL) exit(1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


int URLEncode(const char *str, const int strSize, char *result, const int resultSize) {
    int i;
    int j = 0;//for result index
    char ch;

    if ((str == NULL) || (result == NULL) || (strSize <= 0) || (resultSize <= 0)) {
        return 0;
    }

    for (i = 0; (i < strSize) && (j < resultSize); ++i) {
        ch = str[i];
        if (((ch >= 'A') && (ch < 'Z')) ||
            ((ch >= 'a') && (ch < 'z')) ||
            ((ch >= '0') && (ch < '9'))) {
            result[j++] = ch;
        } else if (ch == ' ') {
            result[j++] = '+';
        } else if (ch == '.' || ch == '-' || ch == '_' || ch == '*') {
            result[j++] = ch;
        } else {
            if (j + 3 < resultSize) {
                sprintf(result + j, "%%%02X", (unsigned char) ch);
                j += 3;
            } else {
                return 0;
            }
        }
    }

    result[j] = '\0';
    return j;
}



void releaseHttp(ft_http_client_t *client) {
    ft_http_destroy(client);
    ft_http_exit(client);
    ft_http_deinit();
}


int http_client_get(char* url, char* data) {
	char *url_path = joinString(url, data);
	
	ft_http_init();
	ft_http_client_t* client = ft_http_new();

	char* result = ft_http_sync_request(client, url_path, M_GET, NULL);
	int error_code = ft_http_get_error_code(client);
	if (error_code == ERR_OK) {
		int n_out_len = strlen(result);
		char *p_tmp = (char *)malloc(n_out_len + 1);
		memcpy(p_tmp, result, n_out_len);
		p_tmp[n_out_len] = 0;

		printf("RET:\n%s\n", p_tmp);

	}

	releaseHttp(client);
	
	return error_code;
}

int http_client_post(char* url, char* data) {
	ft_http_init();
	ft_http_client_t* client = ft_http_new();

	char* result = ft_http_sync_request(client, url, M_POST, data);
	int error_code = ft_http_get_error_code(client);
	if (error_code == ERR_OK) {
		int n_out_len = strlen(result);
		char *p_tmp = (char *)malloc(n_out_len + 1);
		memcpy(p_tmp, result, n_out_len);
		p_tmp[n_out_len] = 0;

		printf("RET:\n%s\n", p_tmp);

	}

	releaseHttp(client);
	
	return error_code;	

}




int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Usage: %s <http_url>\n", argv[0]);
		printf("eg:\n");
	    printf("%s http://127.0.0.1:80/test/\n", argv[0]);
		exit (0);
	}

	char *url_path = argv[1];
	char  http_data[1024] = {0};
	int   ret = 0;

	printf("%s %s start...\n", argv[0], url_path);

		
	printf("Please enter http method(g=GET, p=POST,q=exit) :\n");
	char ch = getchar();

         
	if (ch == 'q') {
		printf("\nWARNNING: exit now!\n");
		exit (0);
	}

    printf("Please enter http data:\n");
	memset(http_data, 0, sizeof(http_data));
	scanf("%s", http_data);
		
	switch (ch) {
	case 'g': {
		printf("HTTP GET: %s/%s\n", url_path, http_data);
		ret = http_client_get(url_path, http_data);
		if (ret != 0) {
			printf("http_client_get failed!\n");
		}
	}
  	break;
	case 'p': {
		printf("HTTP POST: %s\n \"%s\"\n", url_path, http_data);
		ret = http_client_post(url_path, http_data);
		if (ret != 0) {
			printf("http_client_post failed!\n");
		}
	}
	break;
	default:
		printf("Unknown method : %c\n", ch);
	}

    return 0;
}
