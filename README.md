### Quick Start 

```
git clone https://github.com/derekguan/deSPI.git

cd deSPI/src

make

cd ..

./deSPI-download -o taxonomy taxonomy  

./deSPI-index test/refs/ref2tid.map taxonomy/nodes.dmp bin index

bin/deSPI classify index test/reads/reads.fa >Labels
```

---

### Introduction

deSPI is a novel read classification tool which classifies reads by recognizing and analyzing the matches between reads and reference with de Bruijin graph-based lightweight reference indexing.
 
deSPI is mainly designed by Dr. Bo Liu and developed by Mr. Dengfeng Guan with the supervision of Prof. Yadong Wang in Center for Bioinformatics, Harbin Institute of Technology, China.

### Parameters
#### deSPI-download
```
deSPI-download [<options>] <database>

ARGUMENT
 <database>        One of refseq, genbank, or taxonomy:
                     - use refseq or genbank for genomic sequences,
                     - taxonomy for taxonomy mappings.

COMMON OPTIONS
 -o <directory>         Directory to which the files are downloaded. Default: '.'.
 -P <# of threads>      Number of processes when downloading (uses xargs). Default: '1'

WHEN USING database refseq OR genbank:
 -d <domain>            What domain to download. One or more of bacteria, viral, archaea (comma separated).
 -a <assembly level>    Only download genomes with the specified assembly level. Default: 'Complete Genome'.
 -c <refseq category>   Only download genomes in the specified refseq category. Default: any.
 -g                     Download GI map.
```
#### deSPI-index
```
deSPI-index <TID_REF_MAP> <NODE_PATH> <DESPI_BIN_DIR> <INDEX_DIR>

ARGUMENT
    <TID_REF_MAP>            map file list reference path and its taxonomy id.
    <NODE_PATH>              location of nodes.dmp file.
    <DESPI_BIN_DIR>          directory of deSPI execuative files.
    <INDEX_DIR>              directory to store deSPI's index.
``` 
#### deSPI 
```
Usage:     deSPI classify [Options] <IndexDir> <ReadFiles>

<IndexDir>             directory to store the reference index file of deSPI
<ReadFiles>            reads files to process, in FASTQ/FASTA format (separated by space)
Options:   -s, --seed_len      <uint8_t>          lower bound of seed length [30]
           -t, --threads       <int>              # of threads [1]
           -h, --help                             help
```

### Memory Requirements

The memory footprint of deSPI is relatively small for read classification, e.g., using the 12274 RefSeq complete genomes (5975 bacterial, 219 archaea, 6080 viral genomes) as reference, deSPI requires 25 gigabytes to classify the input reads. However, it is worthnoting that, deSPI requires relatively large memory to construct the reference index, e.g., it requires over 100 gigabytes to construct the index of RefSeq complete genomes. This is mainly due to the index construction of deSPI is still under optimization.The memory footprint will be much lower in the later version.

To make it easier to use, we provide a pre-built index of  RefSeq complete genomes, which is available at:
https://drive.google.com/open?id=0Bwibkj8plEJrSExWMm1LcXFWNnc
### User's Guide

#### Database download
Users can take the following command to build their own reference library. All reference genomes will be download from NCBI genbank or refseq.

```
cd deSPI

bin/deSPI-download -o LOCAL_REF_DIR -P THREAD_NUM -d DOMAIN DATABASE 

```
DOMAIN includes viral, bacteria, archaea

DATABSE includes refseq, genbank, taxonomy



#### Index construction
After creating a reference library, the reference index can be constructed by the following command. Since deSPI needs nodes.dmp as input, nodes.dmp requires be downloaded in advance (recommend to use deSPI-download).
```
cd deSPI

bin/deSPI-index  $LOCAL_REF_DIR/ref2tid.map taxonomy/nodes.dmp bin INDEX_DIR

```
---

#### Read classfication
With the constructed index, use the following command to run deSPI to classify reads.

```
cd deSPI

bin/deSPI classify INDEX_DIR READS_FILES >Labels

```
---

#### Output Format
Each sequence classified by deSPI outputs a single line. Each line contains four/three tab-delimited fields; from left to right, they are:
1. "C"/"U": the letter indicates whether the sequence is classified or not.
2. The sequence ID, obtained from the FASTA/FASTQ header.
3. The taxonomy ID used to label the sequence; 0 if the sequence is unclassified.
4. the score of Labels, could be missing if there is no match between read and references.

For example:

           C	ERR636248.35	177416	177416:191           
indicates that the Sequence "ERR636248.35" is assigned to taxononmy ID 177416, and the score of 177416 is 191.

---

### Real sequencing and Simulated datasets
We benchmarked deSPI with two 'pseudo' real metagenome datasets respectively prduced by Illumina HiSeq and MiSeq platforms. Each of them consists of 20 datasets (50,000 reads per datasets). And we also used RefSeq genomes to generate a simulated dataset, we used Mason simulator to produce 1 million 100 bp Illumina-like reads. All datasets are available at:
https://drive.google.com/open?id=0Bwibkj8plEJrSExWMm1LcXFWNnc

---

### Contact
For advising, bug reporting and requiring help, please contact dfguan@hit.edu.cn 
