# MagicUI
一款基于MFC类库的界面皮肤库
<br/>
<br/><b>一、MagicUI简介</b><br/>
MagicUI是一款基于MFC类库的界面皮肤库。MagicUI采用VC6.0编写，调用MFC动态链接库生成，适用于MFC项目开发。皮肤定义采用XML文档标签表示，经MagicUI读取、解析后，生成相应的控件，这些控件均由MFC控件重新封装而成，界面设计更为强大，而功能实现保持不变。这有助于让程序员从繁重的工作中解脱出来，把界面设计交由美工。美工只需要熟悉XML标签定义就可以高效地设计出完美的界面来。程序员则只需调用MagicUI里的封装类实现具体功能。<br/>
<br/><b>二、MagicUI标签说明</b><br/>
1、MagicUI采用XML自定义标签。标签由标签属性和标签内容组成，如：<Window Name=”MainWnd” Rect=”0,0,500,400”><Button Name=”btn” /></Window>。其中Window标签的属性有Name、Rect，内容为<Button Name=”btn” />（也是标签）。<br/>
2、标签名及属性名区分大小写，并遵照MagicUI的命名约定。属性值不区分大小写，但建议适当大小写以增强代码可读性。所有标签均有Name属性，这是必需的，因为它是区分不同控件的主要标识。除此之外，还有一些常用标签，如：Rect表示控件矩形区域，Background为控件背景图片（只能是BMP格式），Image为控件背景图片（可以是JPG、GIF、PNG、BMP等格式），Visible为控件可见性，Enable为控件可用性，ToolTip为工具提示，Cmd为控件响应事件的命令ID。<br/>
<br/><b>三、MagicUI类库介绍</b><br/>
1、熟悉MagicUI所封装的类库，是应用MagicUI进行编程的基础。MagicUI出除了提供动态链接库文件(.dll)外，还提供了类定义头文件(.h)及类导出描述文件（.lib）。在程序工作目录下放置.dll文件，并在工程项目中引用.h和.lib文件，就可以随意的调用MagicUI类库了。<br/>
2、MagicUI类库中，封装了一系列的窗体控件及功能模块，所有类由CMagic--打头。如：CMagicWnd类、CMagicButton类、CMagicPicture类、CMagicText类等，分别对应XML标签中的Window窗体标签、Button按钮标签、Picture图片标签、Text文本标签等。“MagicUI封装类——XML标签——MFC类”对应图表如下：<br/>
Window		->CMagicWnd			:CWnd<br/>
Button		->CMagicButton		:CButton(V)<br/>
CheckBox	->CMagicCheck		:CButton(V)<br/>
RadioBox	->CMagicRadio		:CButton(V)<br/>
ComboBox	->CMagicCombo		:CComboBox(V)<br/>
ListBox		->CMagicList		:CListBox(V)<br/>
EditBox		->CMagicEdit		:CEdit(V)<br/>
GroupBox	->CMagicGroup		:CStatic(V)<br/>
Picture		->CMagicPicture		:CStatic(V)<br/>
Text		->CMagicText		:CStatic(V)<br/>
ScrollBar	->CMagicScroll		:CScrollBar(V)<br/>
Spin		->CMagicSpin		:CSpinButtonCtrl(V)<br/>
Progress	->CMagicProgress	:CProgressCtrl(V)<br/>
Slider		->CMagicSlider		:CSliderCtrl(V)<br/>
ListCtrl	->CMagicListCtrl	:CListCtrl(V)<br/>
TreeCtrl	->CMagicTreeCtrl	:CTreeCtrl(V)<br/>
TabCtrl		->CMagicTabCtrl		:CTabCtrl(V)<br/>
Menu		->CMagicMenu		:CMenu<br/>
ToolBar		->CMagicToolBar		:CToolBar<br/>
StatusBar	->CMagicStatusBar	:CstatusBar<br/>
<br/><b>四、标签使用说明</b><br/>
（详见/doc/《开发文档.doc》）
