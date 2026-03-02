# VulnServer
[![CI Status](https://github.com/ins1gn1a/VulnServer-Linux/workflows/build/badge.svg)](https://github.com/ins1gn1a/VulnServer-Linux/actions) 
[![GitHub pull-requests](https://img.shields.io/github/issues-pr/ins1gn1a/VulnServer-Linux.svg)](https://GitHub.com/ins1gn1a/VulnServer-Linux/pulls/)
[![GitHub contributors](https://img.shields.io/github/contributors/ins1gn1a/VulnServer-Linux.svg)](https://GitHub.com/ins1gn1a/VulnServer-Linux/graphs/contributors/)
[![GitHub issues](https://img.shields.io/github/issues/ins1gn1a/vulnserver-linux)](https://github.com/ins1gn1a/vulnserver-linux/issues)
[![GitHub stars](https://img.shields.io/github/stars/ins1gn1a/vulnserver-linux)](https://github.com/ins1gn1a/vulnserver-linux/stargazers)
[![GitHub license](https://img.shields.io/github/license/ins1gn1a/vulnserver-linux)](https://github.com/ins1gn1a/VulnServer-Linux/blob/master/LICENSE)

This program should not be run on any production systems or networks as it is purposely vulnerable. I will not be held accountable for any usage of this program and you run this at your own risk.

## Prerequisites
```
apt install gcc gcc-multilib
```
## Compile
```
gcc vuln.c -o vuln -fno-stack-protector -z execstack -mpreferred-stack-boundary=2 -m32
```

## Exploits 
A list of exploit is in the directory exploits. Don't look at it for more challenge ! I didn't list everything but I wrote some of the most common exploit for educational purpose
## References
Inspiration from [Stephen Bradshaw's vulnserver](https://github.com/stephenbradshaw/vulnserver/)!
