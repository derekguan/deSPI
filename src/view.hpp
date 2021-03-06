/*
 * =====================================================================================
 *
 *       Filename:  view.hpp
 *
 *    Description:  output taxonomy-specific sequence 
 *
 *        Version:  1.0
 *        Created:  06/07/18 08:46:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dengfeng Guan (D. Guan), dfguan@hit.edu.cn
 *   Organization:  Center for Bioinformatics, Harbin Institute of Technology
 *
 * =====================================================================================
 */
#include "bwt.hpp"

#define GFA 1
#define FASTA 2


class view {
	bwt			*bwt_p;
	uint64_t	taxid_n;
	uint32_t	*taxid_tab;
	int			out_fmt;

public:
	int view_all();
	int view_single(uint32_t tax_id);
	int view_single(uint64_t s, string &seq);
	view(bwt *_bwt_p, uint64_t _taxid_n, uint32_t *_taxid_tab, string str_fmt) {
		bwt_p = _bwt_p;
		taxid_n = _taxid_n;
		taxid_tab = _taxid_tab;
		if (!strcmp(str_fmt.c_str(), "fasta"))
			out_fmt = FASTA;
		else
			out_fmt = GFA;
	}
};



