#! usr/bin/perl

=pod
コーディング規則
関数を書く上で、 単語ごとには必ず大文字にする(前置詞も、冠詞も含む）
変数に関しては、全て小文字にする。
単語ごとにはアンダーバーを入れる
（例）
URL_Download_To_File
Return_Arguments_In_the_Fuction
int retrutn_of_arguments = 32;

=cut

my @seed_answers;
my @key_answers;


my $infile = <STDIN>;
open(IN, "$infile") or die "open err: $infile";
@data = <IN>;
close(IN);

our $seed_flag = 0;
our $key_flag = 0;

foreach $datafile(@data) {

    if($datafile =~ /(................................)(67.01.)(...............)/) {
        print "seed is $3\n";
    }

    if($datafile =~ /(................................)(27.02.)(...............)/) {
        print "key is  $3\n";
    }


    if($datafile =~ /(................................)(12.67.01.)(............)/) {

        print "seed(1) is $3\n";
    }

    if($datafile =~ /(.............................)(21.)(..................)/) {
        print "(2) $3\n";

    }

    if($datafile =~ /(.............................)(22.)(..................)/) {

        print "(3) $3\n";
    }


    if($datafile =~ /(................................)(12.27.02.)(............)/) {

        print "key(1) is $3\n";
    }

}
