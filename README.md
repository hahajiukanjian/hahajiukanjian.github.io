# 欢迎

这里是哈哈就看见的个人网站Git仓库

## 网站生成步骤
1. 编写-markdown格式个人笔记
2. 生成-[mkdocs](https://www.mkdocs.org)
3. 主题-[Material](https://github.com/squidfunk/mkdocs-material)
4. 发布-[Github Pages](https://pages.github.com)
5. 自动化-[Github Actions](https://github.com/features/actions)

## 遇到的困难
- **`Q`** Github Actions 生成html文件并发布到Github Pages后，访问hahajiukanjian.githun.io没有出现以Material为主题的笔记文档，而是出现了README.md中的内容<br>
- **`A`** 在仓库的`settings`中的`pages`里，将分支从`main`改为`gh-pages`，并将根目录从`root`改为`/docs`

- **`Q`** 将目录从/改为/docs后，GitHub Actions出错`Error: No such file or directory @ dir_chdir - /github/workspace/docs`
- **`A`** 阅读GitHub Pages文档后，需要将目录改回为根目录/


