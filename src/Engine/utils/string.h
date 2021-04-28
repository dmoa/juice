#pragma once

struct string {
    char* str;
    u8 len;
};

inline string strmalloc(const char* src_str) {
	string s = { (char*) malloc(sizeof(char) * (strlen(src_str)) + 1), strlen(src_str)};
    strcpy(s.str, src_str);
    return s;
};

inline void strfree(string* s) {
    if (! s) return;
    free(s->str);
    s->len = 0;
};

inline bool strequal(const char* a, const char* b) { return strcmp(a, b) == 0; }