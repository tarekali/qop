cat <<EOF
Test scripts for qop.
Wang Bin <wbsecg1@gmail.com>
2011-04-20

EOF

export PATH=../bin:$PATH
qop="qop"; type -p $qop 2>/dev/null
[ $? -ne 0 ] && qop="qop.exe"; type -p $qop 2>/dev/null
[ $? -ne 0 ] && qop="qop-maemo5"; type -p $qop 2>/dev/null
[ $? -ne 0 ] && qop="qop-ezx"; type -p $qop 2>/dev/null
[ $? -ne 0 ] && echo 'qop not found. Please set the PATH' && exit
