###使用UEFI模式安装双系统。

下面是我的`VN7-591G-51SS`笔记本在装`Linux`遇到的问题，默认开启`secure boot`模式的，需要关闭这个，使用`legacy`这个模式同样是没有关闭`secure boot`的，我也是在网上搜索，折腾了一天才搞定这个问题的。
其实要设置`secure boot`很简单，只需要设置bios的超级密码，即可修改这个模式了。

安装Linux 其他发行版比如MINT 安装失败 最后`efi`写不进去，尝试了一下，应该是`mount`上去的时候是`read-only`，需要用`root`挂载安装才行。
我默认安装的`Kali`发行版。成功安装！！


在过程中，我不停的折腾，把`win8`和`linux`都弄挂了好几次，所以重装了10来次，包括尝试其他`Linux`发行版。

默认安装好的`win8`很卡，很多垃圾的东西，所以我自己下了一个`win8`纯净版本的，装上后自己升级到8.1把自己需要的装上就可以了。

`Linux Kali`安装默认是没办法进去的，需要使用`refind`来引导整个盘上的所有系统。网上也有其他的解决方案。我这里直接用的`refind`，

安装完成后默认进入的是`win8`，所以使用`DiskGenius`挂载修改`refind`即可。也可以用`win`默认自带的`diskpart`命令，不过很麻烦，特别对我们这种`win`小白，连命令都搞不清楚的。而且修改文件貌似是权限拒绝的。我反正没弄正确，so，直接使用DiskGenius工具查看修改。

下载最新`refind-0.8.7`，只需要解压出来把里面的`refind`文件夹`copy`进去即可。使用`bcdedit /set `命令修改win8默认的引导文件，完整的命令`bcdedit /set {bootmgr} path \EFI\refind\refind_x64.efi`

详细可以[参考](http://www.rodsbooks.com/refind/installing.html)
