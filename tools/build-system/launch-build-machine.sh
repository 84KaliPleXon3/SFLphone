#!/bin/bash
#####################################################
# File Name: launch-build-machine.sh
#
# Purpose :
#
# Author: Julien Bonjean (julien@bonjean.info) 
#
# Creation Date: 2009-04-20
# Last Modified:
#####################################################

TAG=`date +%Y-%m-%d`

# wait delay after startup and shutdown of VMs
STARTUP_WAIT=40
SHUTDOWN_WAIT=30

# ssh stuff
SSH_OPTIONS="-o LogLevel=ERROR -o CheckHostIP=no -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null"
SSH_HOST="sflphone@127.0.0.1"
SSH_REPOSITORY_HOST="sflphone-package-manager@dev.savoirfairelinux.net"
SSH_BASE="ssh ${SSH_OPTIONS} -p 50001 ${SSH_HOST}"
SCP_BASE="scp ${SSH_OPTIONS} -r -P 50001"

# home directory
ROOT_DIR="/home/projects/sflphone"

# vbox config directory
export VBOX_USER_HOME="${ROOT_DIR}/vbox"

# remote home directory
REMOTE_ROOT_DIR="/home/sflphone"

# scripts
SCRIPTS_DIR="${ROOT_DIR}/build-system"
PACKAGING_SCRIPTS_DIR="${SCRIPTS_DIR}/remote"
BIN_DIR="${SCRIPTS_DIR}/bin"

# directory that will be deployed to remote machine
TODEPLOY_DIR="${ROOT_DIR}/sflphone-packaging"
TODEPLOY_BUILD_DIR="${TODEPLOY_DIR}/build"

# remote deployment dir
REMOTE_DEPLOY_DIR="/home/sflphone/sflphone-packaging"

# cloned repository and archive
REPOSITORY_DIR="${TODEPLOY_BUILD_DIR}/sflphone"
REPOSITORY_ARCHIVE="`dirname ${REPOSITORY_DIR}`/sflphone.tar.gz"
REPOSITORY_SFLPHONE_COMMON_DIR="${REPOSITORY_DIR}/sflphone-common"
REPOSITORY_SFLPHONE_CLIENT_KDE_DIR="${REPOSITORY_DIR}/sflphone-client-kde"
REPOSITORY_SFLPHONE_CLIENT_GNOME_DIR="${REPOSITORY_DIR}/sflphone-client-gnome"

# where results go
PACKAGING_RESULT_DIR=${ROOT_DIR}/packages-${TAG}

USER="sflphone"

RELEASE_MODE=
VERSION_APPEND=

DO_PREPARE=1
DO_MAIN_LOOP=1
DO_SIGNATURES=1
DO_UPLOAD=1
DO_LOGGING=1
DO_SEND_EMAIL=1

EDITOR=echo
export EDITOR

MACHINES=( "ubuntu-8.04" "ubuntu-8.04-64" "ubuntu-8.10" "ubuntu-8.10-64" "ubuntu-9.04" "ubuntu-9.04-64" )

#########################
# BEGIN
#########################

echo
echo "    /***********************\\"
echo "    | SFLPhone build system |"
echo "    \\***********************/"
echo

cd ${SCRIPTS_DIR}

if [ "$?" -ne "0" ]; then
        echo " !! Cannot cd to working directory"
        exit -1
fi

WHO=`whoami`

if [ "${WHO}" != "${USER}" ]; then
        echo "!! Please use user ${USER} to run this script"
        exit -1;
fi

for PARAMETER in $*
do
	case ${PARAMETER} in
	--help)
		echo
		echo "Options :"
		echo " --skip-prepare"
		echo " --skip-main-loop"
		echo " --skip-signatures"
		echo " --skip-upload"
		echo " --no-logging"
		echo " --machine=MACHINE"
		echo " --release-mode=[beta|rc|release]"
		echo " --list-machines"
		echo
		exit 0;;
	--skip-prepare)
		unset DO_PREPARE;;
	--skip-main-loop)
		unset DO_MAIN_LOOP;;
	--skip-signatures)
		unset DO_SIGNATURES;;
	--skip-upload)
		unset DO_UPLOAD;;
	--no-logging)
		unset DO_LOGGING;;
	--machine=*)
		MACHINES=(${PARAMETER##*=});;
	--release-mode=*)
		RELEASE_MODE=(${PARAMETER##*=});;
	--list-machines)
		echo "Available machines :"
		for MACHINE in ${MACHINES}; do
			echo " "${MACHINE}
		done
		exit 0;;
	*)
		echo "Unknown parameter : ${PARAMETER}"
		exit -1;;
	esac
done

# logging
mkdir ${PACKAGING_RESULT_DIR} 2>/dev/null
if [ ${DO_LOGGING} ]; then

	# open file descriptor
	rm -f ${PACKAGING_RESULT_DIR}/packaging.log
	exec 3<> ${PACKAGING_RESULT_DIR}/packaging.log

	# redirect outputs (stdout & stderr)
	exec 1>&3
	exec 2>&3
fi

# check release
if [ ${RELEASE_MODE} ]; then
	case ${RELEASE_MODE} in
		beta);;
		rc[1-9]);;
		release);;
		*)
			echo "Bad release mode"
			exit -1;;
	esac
fi

# check machines list
if [ -z "${MACHINES}" ]; then
	echo "Need at least a machine name to launch"
	exit -1
fi

echo
echo "Launching build system with the following machines :"
for MACHINE in ${MACHINES[*]}
do
	echo " "${MACHINE}
done
echo

if [ ${RELEASE_MODE} ]; then
	echo "Release mode : ${RELEASE_MODE}"
	if [ "${RELEASE_MODE}" != "release" ];then
		VERSION_APPEND="~${RELEASE_MODE}"
	fi
else
	echo "Snapshot mode"
fi

#########################
# COMMON PART
#########################

if [ ${DO_PREPARE} ]; then

	echo
	echo "Cleaning old deploy dir"
	rm -rf ${TODEPLOY_DIR}
	mkdir ${TODEPLOY_DIR}
	mkdir ${TODEPLOY_BUILD_DIR}

	echo "Clone repository"
	git clone ssh://repos-sflphone-git@sflphone.org/~/sflphone.git ${REPOSITORY_DIR} >/dev/null 2>&1


	if [ "$?" -ne "0" ]; then
		echo " !! Cannot clone repository"
		exit -1
	fi

	FULL_VER=`cd ${REPOSITORY_DIR} && git describe --tag HEAD  | cut -d "/" -f2 | cut -d "-" -f1-2`
	
	# change current branch if needed
        if [ ${RELEASE_MODE} ]; then
                cd ${REPOSITORY_DIR}
                echo "Using release branch"
                git checkout origin/release -b release
        else
                echo "Using master branch"
        fi

	# generate the changelog, according to the distribution and the git commit messages
	echo "Update changelogs"

	# use git to generate changelogs
	# TODO : currently do symlink to workaround git-dch bug, check if better way is possible
	if [ ${RELEASE_MODE} ]; then
	        cd ${REPOSITORY_DIR} && ln -s ${REPOSITORY_SFLPHONE_COMMON_DIR}/debian/ . && ${BIN_DIR}/git-dch -a -R -N "${FULL_VER}${VERSION_APPEND}" --debian-branch=release && rm debian && \
		# cd ${REPOSITORY_DIR} && ln -s ${REPOSITORY_SFLPHONE_CLIENT_KDE_DIR}/debian . && ${BIN_DIR}/git-dch -a -R -N "${FULL_VER}${VERSION_APPEND}" --debian-branch=release && rm debian && \
		cd ${REPOSITORY_DIR} && ln -s ${REPOSITORY_SFLPHONE_CLIENT_GNOME_DIR}/debian . && ${BIN_DIR}/git-dch -a -R -N "${FULL_VER}${VERSION_APPEND}" --debian-branch=release && rm debian
	else
		cd ${REPOSITORY_DIR} && ln -s ${REPOSITORY_SFLPHONE_COMMON_DIR}/debian . && ${BIN_DIR}/git-dch -a -S && rm debian && \
		# cd ${REPOSITORY_DIR} && ln -s ${REPOSITORY_SFLPHONE_CLIENT_KDE_DIR}/debian . && ${BIN_DIR}/git-dch -a -S && rm debian && \
		cd ${REPOSITORY_DIR} && ln -s ${REPOSITORY_SFLPHONE_CLIENT_GNOME_DIR}/debian . && ${BIN_DIR}/git-dch -a -S && rm debian
	fi
	
	if [ "$?" -ne "0" ]; then
		echo "!! Cannot update changelogs"
		exit -1
	fi

	# change UNRELEASED flag to system as we alway do a build for each distribution
	# and distribution is set by another script
	find ${REPOSITORY_DIR} -name changelog -exec sed -i 's/UNRELEASED/SYSTEM/g' {} \;

	cd ${REPOSITORY_DIR}	
	echo "Update repository with new changelog"
	echo " Switch to master branch to commit"
	if [ ${RELEASE_MODE} ]; then
                
                echo "Switch to master branch for commit"
                git checkout master
        fi

	echo " Doing commit"
	VERSION_COMMIT=${FULL_VER}${VERSION_APPEND}
	if [ ! ${RELEASE_MODE} ]; then
		VERSION_COMMIT=${FULL_VER}" Snapshot ${TAG}"
	fi
	git-commit -m "[#1262] Updated changelogs for version ${VERSION_COMMIT}" . >/dev/null
	echo " Pushing commit"
	git push origin master >/dev/null

	# change back current branch if needed
	if [ ${RELEASE_MODE} ]; then
		echo "Switch back to release branch"
		git checkout release
		git merge master
	fi
	
	echo "Archiving repository"
	tar czf ${REPOSITORY_ARCHIVE} -C `dirname ${REPOSITORY_DIR}` sflphone 

	if [ "$?" -ne "0" ]; then
		echo " !! Cannot archive repository"
		exit -1
	fi

	echo  "Removing repository"
	rm -rf ${REPOSITORY_DIR}

	echo "Finish preparing deploy directory"
	cp -r ${PACKAGING_SCRIPTS_DIR}/* ${TODEPLOY_DIR}

	if [ "$?" -ne "0" ]; then
		echo " !! Cannot prepare scripts for deployment"
		exit -1
	fi
fi

#########################
# MAIN LOOP
#########################

if [ ${DO_MAIN_LOOP} ]; then

	echo
	echo "Entering main loop"
	echo

	for MACHINE in ${MACHINES[*]}
	do

		echo "Launch machine ${MACHINE}"
		VM_STATE=`VBoxManage showvminfo ${MACHINE} | grep State | awk '{print $2}'`
		if [ "${VM_STATE}" = "running" ]; then
			echo "Not needed, already running"
		else
			cd ${VBOX_USER_HOME} && VBoxHeadless -startvm "${MACHINE}" -p 50000 &
			echo "Wait ${STARTUP_WAIT} s"
			sleep ${STARTUP_WAIT}
		fi
	
		echo "Doing updates"
		${SSH_BASE} 'sudo apt-get update >/dev/null'
		${SSH_BASE} 'sudo apt-get upgrade -y >/dev/null'

		echo "Clean remote directory"
		${SSH_BASE} "rm -rf ${REMOTE_DEPLOY_DIR} 2>/dev/null"

		echo "Deploy packaging system"
		${SCP_BASE} ${TODEPLOY_DIR} ${SSH_HOST}:

		if [ "$?" -ne "0" ]; then
	                echo " !! Cannot deploy packaging system"
	                exit -1
	        fi

		echo "Launch remote build"
		${SSH_BASE} "${REMOTE_DEPLOY_DIR}/build-package-ubuntu.sh ${RELEASE_MODE}"

		if [ "$?" -ne "0" ]; then
	                echo " !! Error during remote packaging process"
	                # exit -1
	        fi

		echo "Retrieve dists and log files (current tag is ${TAG})"
		${SCP_BASE} ${SSH_HOST}:${REMOTE_DEPLOY_DIR}/dists ${PACKAGING_RESULT_DIR}/
		${SCP_BASE} ${SSH_HOST}:${REMOTE_DEPLOY_DIR}"/*.log" ${PACKAGING_RESULT_DIR}/

		if [ "$?" -ne "0" ]; then
	                echo " !! Cannot retrieve remote files"
	                exit -1
	        fi

		if [ "${VM_STATE}" = "running" ]; then
			echo "Leave machine running"
		else
			echo "Shut down machine ${MACHINE}"
			${SSH_BASE} 'sudo shutdown -h now'
			echo "Wait ${SHUTDOWN_WAIT} s"
			sleep ${SHUTDOWN_WAIT}
			echo "Hard shut down"
			cd "${VBOX_USER_HOME}" && VBoxManage controlvm ${MACHINE} poweroff
		fi
	done
fi

#########################
# SIGNATURES
#########################

if [ ${DO_SIGNATURES} ]; then
	
	echo
	echo "Sign packages"
	echo

	echo  "Check GPG agent"
	pgrep -u "sflphone" gpg-agent > /dev/null
	if [ "$?" -ne "0" ]; then
	        echo "!! GPG agent is not running"
		exit -1
	fi
	GPG_AGENT_INFO=`cat $HOME/.gpg-agent-info 2> /dev/null`
	export ${GPG_AGENT_INFO}

	if [ "${GPG_AGENT_INFO}" == "" ]; then
        	echo "!! Cannot get GPG agent info"
	        exit -1
	fi	

	echo "Sign packages"
	find ${PACKAGING_RESULT_DIR} -name "*.deb" -exec dpkg-sig -k 'Savoir-Faire Linux Inc.' --sign builder --sign-changes full {} \; >/dev/null 2>&1
	find ${PACKAGING_RESULT_DIR} -name "*.changes" -printf "debsign -k'Savoir-Faire Linux Inc.' %p\n" | sh >/dev/null 2>&1
fi

#########################
# UPLOAD FILES
#########################

if [ ${DO_UPLOAD} ]; then
	
	echo
	echo "Upload packages"
	echo

	echo "Prepare packages upload"
	scp ${SSH_OPTIONS} ${PACKAGING_SCRIPTS_DIR}/update-repository.sh ${SSH_REPOSITORY_HOST}: 

	if [ "$?" -ne "0" ]; then
                echo " !! Cannot deploy repository scripts"
        fi
	
	echo "Upload packages"
	echo "Install dists files to repository"
	scp -r ${SSH_OPTIONS} ${PACKAGING_RESULT_DIR}/dists ${SSH_REPOSITORY_HOST}:

	if [ "$?" -ne "0" ]; then
		echo " !! Cannot upload packages"
		exit -1
	fi

	echo "Update repository"
	ssh ${SSH_OPTIONS} ${SSH_REPOSITORY_HOST} "./update-repository.sh"

	if [ "$?" -ne "0" ]; then
		echo " !! Cannot update repository"
		exit -1
	fi
fi

# close file descriptor
exec 3>&-

exit 0
