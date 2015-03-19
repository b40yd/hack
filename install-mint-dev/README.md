# Linux开发环境配置

### Emacs开发环境
* Ruby / Ruby on Rails
* CSS / LESS / SASS / SCSS
* HAML / Markdown / Textile / ERB
* Clojure (with Cider and nRepl)
* Javascript / Coffeescript
* Python
* PHP
* Haskell
* Erlang
* Common Lisp (with Slime)
* GO  (Emacs Packages中安装)
* Scheme/Guile (Emacs Packages中安装)
* C/C++

### 其余辅助工具
* Jq (JSON数据排版工具，在命令行下能很漂亮的显示数据格式)
* Httpie
* Cv (查看删除和复制的进度)
* Icdiff (强大的文件对比工具,支持git)
* TextSql (使用sql语句的形式查询csv文件)
* Impress.js (Web版的slide)
* [Linux Commandline](http://www.commandlinefu.com/commands/browse/sort-by-votes) (一个常用的linux 命令分享网站 )
* [oh-my-zsh](https://github.com/robbyrussell/oh-my-zsh.git)(一个zsh的配置)
* fish-shell (提供自动补全，不需要配置)
* atom (一个编辑器，像sublime text)

以上工具提供了脚本直接执行安装。

#### Emacs 配置
我使用的是[purcell/emacs.d](https://github.com/purcell/emacs.d) 这个配置很规范很强大。本身已经配置好了一部分
* Ruby / Ruby on Rails
* CSS / LESS / SASS / SCSS
* HAML / Markdown / Textile / ERB
* Clojure (with Cider and nRepl)
* Javascript / Coffeescript
* Python
* PHP
* Haskell
* Erlang
* Common Lisp (with Slime)

直接使用就是了
```Bash
  git clone https://github.com/purcell/emacs.d.git ~/.emacs.d
```

#### Emacs Go开发环境配置
执行M-x,输入
```Emacs
  package-list-packages
```
会自动打开emacs的配置仓库
然后C-s搜索`*go-autocomplete*` 输入`*i*`就会标记为安装
然后找到`*go-mode*` 一样标记一下
执行`*x*`就会自动安装了。
需要装gocode/godef/cscope[脚本文件](install-emacs.d.sh)
最后需要在~/.emacs.d/init.el中加入以下代码:
```Emacs
  (require 'go-autocomplete):
  (require 'auto-complete-config)
  (define-key ac-mode-map (kbd "M-TAB") 'auto-complete)
```
#### Emacs [Guile](http://www.gnu.org/software/guile/download.html#git)开发环境配置
需要安装[geiser](http://www.nongnu.org/geiser/)，一样直接M-x,输入
```Emacs
  package-list-packages
```
在里面找到geiser安装就可以了。安装guile的解释器
Guile depends on the following external libraries.
- libgmp
- libiconv
- libintl
- libltdl
- libunistring
- libgc
- libffi
libtool 和libgc这两个最好手动安装
```Bash
  wget http://ftpmirror.gnu.org/libtool/libtool-2.4.6.tar.gz
  tar zxvf libtool-2.4.6.tar.gz
  cd libtool-2.4.6
  ./configure
  make -j8
  sudo make install

  wget -c http://ftp.gnu.org/gnu/libunistring/libunistring-0.9.5.tar.xz
  xz -d libunistring-0.9.5.tar.xz
  tar xvf libunistring-0.9.5.tar
  cd libunistring-0.9.5
  ./configure
  make -j8 && make install
  git clone git://github.com/ivmai/bdwgc.git
  cd bdwgc
  git clone git://github.com/ivmai/libatomic_ops.git
  autoreconf -vif
  automake --add-missing
  ./configure
  make -j8
  sudo make install
  git clone git://git.sv.gnu.org/guile.git && cd guile
  ./configure
  make -j8
  make install
```


