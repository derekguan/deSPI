/*
 * =====================================================================================
 *
 *       Filename:  view.cpp
 *
 *    Description:  realization of view.hpp
 *
 *        Version:  1.0
 *        Created:  06/07/18 18:51:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dengfeng Guan (D. Guan), dfguan@hit.edu.cn
 *   Organization:  Center for Bioinformatics, Harbin Institute of Technology
 *
 * =====================================================================================
 */


#include "view.hpp"

int view::view_all()
{
	string nucl_seq;
	uint64_t cnt = 0;
	for ( uint64_t i = 0; i < taxid_n; ++i) {
		int len_seq = view_single(i, nucl_seq);
		if (out_fmt == FASTA) 
			fprintf(stdout, ">%u\n%s\n", taxid_tab[i],nucl_seq.c_str());
		else 
			fprintf(stdout, "S\t%lu\t%s\tLN:i:%d\tTI:I:%u\n",cnt, nucl_seq.c_str(), len_seq, taxid_tab[i]);
		++cnt;
		nucl_seq.clear();		
	}	
	if (!cnt) fprintf(stderr, "No Records in database\n");
	else fprintf(stderr, "%lu Records found in database\n", cnt);
	return 0;
}

int view::view_single(uint64_t s, string &ns)
{
	++s;
	if ( s == taxid_n) s = 0;
	return bwt_p->get_utg(s, ns);	
}

int view::view_single(uint32_t tax_id)
{
	uint64_t i;
	uint64_t cnt = 0;
	string nucl_seq;
	for ( i = 0; i < taxid_n; ++i) 
		if (bwt_p->taxonIDTab[i] == tax_id) {
			int len_seq = view_single(i, nucl_seq);
			if (out_fmt == FASTA) 
				fprintf(stdout, ">%u\n%s\n", tax_id,nucl_seq.c_str());
			else 
				fprintf(stdout, "S\t%lu\t%s\tLN:i:%d\tTI:I:%u\n",cnt, nucl_seq.c_str(), len_seq, tax_id);
			++cnt;
			nucl_seq.clear();
		} 
	if (!cnt)	fprintf(stderr, "No Records found in database\n");
	else fprintf(stderr, "%lu Records found in database\n", cnt);
	return 0;
}




