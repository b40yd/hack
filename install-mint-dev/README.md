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

#### Emacs 配置
我使用的是[purcell/emacs.d](https://github.com/purcell/emacs.d) 这个配置很规范很强大。
本身已经配置好了一部分
    Ruby / Ruby on Rails
    CSS / LESS / SASS / SCSS
    HAML / Markdown / Textile / ERB
    Clojure (with Cider and nRepl)
    Javascript / Coffeescript
    Python
    PHP
    Haskell
    Erlang
    Common Lisp (with Slime)

直接使用就是了
```git
  git clone https://github.com/purcell/emacs.d.git ~/.emacs.d
```

#### Emacs Go开发环境配置
执行M-x,输入
```Emacs
  package-list-packages  
```
会自动打开emacs的配置仓库
然后C-s搜索go-autocomplete 输入i就会标记为安装
然后找到go-mode 一样标记一下
执行x就会自动安装了。
最后需要装gocode/godef/cscope[脚本文件](install-emacs.d.sh)
