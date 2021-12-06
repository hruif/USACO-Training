/*
ID: blackco3
TASK: cryptcow
LANG: C++
*/
#include <iostream>
#include <algorithm>
#include <functional>
#include <ctype.h>
#include <string.h>
using namespace std;
const int _max_len_(80), _n_mark_(3), _n_hash_(736121);//712433) ;
char org_str[_max_len_] = "Begin the Escape execution at the Break of Dawn", len_org = strlen(org_str);
char coded[_max_len_], len_code, mark[_n_mark_ + 1] = "COW";
struct t_hash {
	int val;
	t_hash* next;
} searched[_n_hash_], conflict_buf[_n_hash_], * p_conflict = conflict_buf;

struct t_tries {
	t_tries* next[26];
	t_tries() { memset(next, 0, sizeof(next)); };
} tries_buf[((_max_len_ * _max_len_) >> 1) + 1];

void set_trie(char* cstr) {
	static t_tries* p_tri_tail = tries_buf + 1;
	t_tries* p_tri = tries_buf;
	for (char* pc = cstr; *pc != '\0'; p_tri = p_tri->next[*pc - 'a'], pc++) {
		if (!p_tri->next[*pc - 'a'])
			p_tri->next[*pc - 'a'] = (p_tri_tail++);
	}
}

inline bool check_str(char* p_start, char* p_end) {
	register t_tries* p_trie = tries_buf;
	for (char* pc = p_start; pc != p_end; pc++) {
		p_trie = p_trie->next[*pc - 'a'];
		if (!p_trie)
			return false;
	}
	return true;
}

bool char_comp(char const& c1, char const& c2) {
	return c1 < c2;
}

void trans_low(char* p_start, char* p_end) {
	for (char* pc = p_start; pc != p_end; pc++) {
		if (*pc == ' ')
			*pc = 'z'; // never appeared in target string 
		if (*pc != 'C' && *pc != 'O' && *pc != 'W')
			*pc = tolower(*pc);
	}
}

bool pre_works() {
	int app_times[_n_mark_] = { 0, 0, 0 };
	char en_sort[_max_len_], org_sort[_max_len_];
	strcpy(en_sort, coded);
	len_code = strlen(coded);
	if (coded[len_code - 1] == '\n')
		coded[--len_code] = '\0';

	for (int ic = 0; ic < len_code; ic++) {
		for (int im = 0; im < _n_mark_; im++)
			if (en_sort[ic] == mark[im])
				app_times[im]++, en_sort[ic] = ' ';
	}

	if (app_times[0] != app_times[1] || app_times[1] != app_times[2])
		return false;

	if (len_code - app_times[0] * _n_mark_ != len_org)
		return false;

	strcpy(org_sort, org_str);
	sort(org_sort, org_sort + len_org, char_comp);
	sort(en_sort, en_sort + len_code, char_comp);
	for (int i = 0; i < len_org; i++)
		if (en_sort[i + app_times[0] * _n_mark_] != org_sort[i])
			return false;
	trans_low(coded, coded + len_code);
	trans_low(org_str, org_str + len_org);
	for (char* pc = org_str; pc != org_str + len_org; pc++)
		set_trie(pc);
	return true;
}

inline int ELF_hash(char* p_start, char* p_end) {
	unsigned long h = 0, g;
	for (char* pc = p_start; pc != p_end; pc++) {
		h = (h << 4) + *pc;
		g = h & 0xf0000000l;
		if (g)
			h ^= g >> 24;
		h &= ~g;
	}
	return h;
}

inline int SDBM_hash(char* p_start, char* p_end) {
	int hash = 0;
	for (char* pc = p_start; pc != p_end; pc++)
		hash = (*pc) + (hash << 6) + (hash << 16) - hash;
	return (hash & 0x7FFFFFFF);
}

bool check_code(char* cur_code, int cur_len) {
	if (cur_len == len_org)
		return !strcmp(cur_code, org_str);

	char* pre_mark = 0;
	for (char* pc = cur_code, *pre = cur_code, tmp = 0; pc != cur_code + cur_len + 1; pc++) {
		if (*pc != 'C' && *pc != 'O' && *pc != 'W' && *pc != '\0')
			continue;
		if (!pre_mark && *pc != 'C' && *pc != '\0')
			return false;
		if (*pc == '\0' && pre_mark && *pre_mark != 'W')
			return false;
		pre_mark = pc;
		if (!check_str(pre, pc))
			return false;
		pre = pc + 1;
	}

	int elf_hval = ELF_hash(cur_code, cur_code + cur_len) % _n_hash_;
	int sdbm_hval = SDBM_hash(cur_code, cur_code + cur_len);
	t_hash* p_hash = searched + elf_hval;
	if (!(p_hash->val))
		p_hash->val = sdbm_hval;
	else {
		do {
			if (p_hash->val == sdbm_hval)
				return false;
			if (!p_hash->next)
				break;
			p_hash = p_hash->next;
		} while (1);
		p_hash->next = p_conflict++;
		p_hash->next->val = sdbm_hval;
	}

	char tmp_code[_max_len_];
	for (int io = 0; io < cur_len; io++) {
		if (cur_code[io] != 'O')
			continue;
		for (int ic = 0; ic < cur_len; ic++) {
			if (cur_code[ic] != 'C')
				continue;
			for (int iw = 0; iw < cur_len; iw++) {
				if (cur_code[iw] != 'W')
					continue;
				if (ic > io || io > iw)
					continue;
				memcpy(tmp_code, cur_code, ic);
				memcpy(tmp_code + ic, cur_code + io + 1, iw - io - 1);
				memcpy(tmp_code + ic + iw - io - 1, cur_code + ic + 1, io - ic - 1);
				memcpy(tmp_code + iw - 2, cur_code + iw + 1, cur_len - iw);

				if (check_code(tmp_code, cur_len - _n_mark_))
					return true;
			}
		}
	}
	return false;
}

int main() {
	freopen("cryptcow.in", "r", stdin);
	freopen("cryptcow.out", "w", stdout);
	fgets(coded, _max_len_, stdin);
	if (!pre_works()) {
		cout << "0 0" << endl;
		return 0;
	}
	if (check_code(coded, len_code))
		cout << "1 " << (strlen(coded) - len_org) / 3 << endl;
	else
		cout << "0 0\n";

	return 0;
}