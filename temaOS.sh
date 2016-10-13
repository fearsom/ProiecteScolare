####check user
function checkUser {
cifre='^[0-9]+$'
litere='[a-zA-Z]'
for char in $(sed -e 's/\(.\)/\1\n/g'	 <<<$user); do
	if  ! [[ $char =~ $cifre ]] ; then
	if  ! [[ $char =~ $litere ]] ; then
		echo " Username is not valid" >&2; exit 1
	fi	
	fi
done
}

####check email
function checkMail {
countA=0
re='^[0-9]+$'
se='[a-zA-Z]'
for i in $(seq 1 ${#email}); do
	if [[ ${email:i-1:1} = '@' ]] ; then
		((countA++))
		pozitieA=$index
	fi
	if [[ ${email:i-1:1} = '.' ]] && 
	[[ ${email:i:1} = '.' ]]; then 
	echo "Invalid e-mail" >&2; exit 1
	fi 
	if [[ ${email:0:1} = '.' ]] || 
	[[ ${email:${#email}-1:1} = '.' ]]; then
	echo "Invalid e-mail" >&2; exit 1
	fi
done
if [[ $countA == 1 ]]; then 
 
	for i in $(seq 1 ${#email}); do
		if  ! [[ ${email:i-1:1} = '.' ]]; then 
		if   ! [[ ${email:i-1:1} = '_' ]]; then   
		if   ! [[ ${email:i-1:1} =~ $re ]]; then  
		if   ! [[ ${email:i-1:1} =~ $se ]]; then 
		if   ! [[ ${email:i-1:1} = '@' ]]; then 
		echo "Invalid e-mail" >&2; exit 1
		fi
		fi
		fi
		fi
		fi
	done
else 
 echo "Invalid e-mail" >&2; exit 1

fi
}

####check password
function checkPassword {
contorLitere=0
litereMari='[A-Z]'
if [[ ${#password} <4 ]]; then
	echo "Password is too short" >&2; exit 1
fi
for i in $(seq 1 ${#password}); do
	if [[ ${password:i-1:1} =~ $litereMari ]]; then
		((contorLitere++))
	fi
done
if [[ $contorLitere -eq 0 ]]; then 
	echo "Password is insecure" >&2; exit 1
fi
}

###main
while getopts ":u:p:e:" opt; do
	case $opt in
	u) user=$OPTARG 
	   checkUser $user
	;;
	e) email=$OPTARG 
	   checkMail $email 
	;;
	p) password=$OPTARG 
	   checkPassword $password 
	;;
	\?) echo "Invalid option: -$OPTARG" 
	;;
	:) echo "Option -$OPTARG require an argument" 
	exit 1
	;;
	esac
done
contorArgumente=0
for i in $*; do
	((contorArgumente++))
done
	if [[ $contorArgumente = 0 ]]; then
		echo "Require an argument" >&2; exit 1
	fi
if [[ -n $password ]]; then 
echo "User $user has password $password and e-mail $email "
	else
echo "User $user has email $email "
fi

