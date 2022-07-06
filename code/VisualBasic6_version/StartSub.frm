VERSION 5.00
Object = "{6BF52A50-394A-11D3-B153-00C04F79FAA6}#1.0#0"; "wmp.dll"
Begin VB.Form StartSub 
   Caption         =   "大家好"
   ClientHeight    =   6270
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   11175
   Icon            =   "StartSub.frx":0000
   LinkTopic       =   "Form1"
   Picture         =   "StartSub.frx":000C
   ScaleHeight     =   6270
   ScaleWidth      =   11175
   StartUpPosition =   3  '窗口缺省
   Begin VB.CheckBox noSoundC 
      Caption         =   "静音"
      Height          =   255
      Left            =   9360
      TabIndex        =   8
      Top             =   0
      Width           =   735
   End
   Begin VB.CommandButton settingsB 
      Caption         =   "游戏设置"
      Height          =   495
      Left            =   10200
      TabIndex        =   7
      Top             =   5280
      Width           =   975
   End
   Begin VB.CommandButton ExitGameB 
      Caption         =   "退出游戏"
      Height          =   495
      Left            =   9840
      TabIndex        =   6
      Top             =   5760
      Width           =   1335
   End
   Begin VB.CommandButton StartGameShoot 
      Caption         =   "    蔡徐坤射鸡     (开发中,可能有bug)"
      Height          =   495
      Left            =   240
      TabIndex        =   5
      Top             =   4560
      Width           =   1815
   End
   Begin VB.CheckBox bgFlash 
      Caption         =   "动态背景"
      Height          =   255
      Left            =   10080
      TabIndex        =   4
      Top             =   0
      Width           =   1095
   End
   Begin VB.Timer bgCtrl 
      Enabled         =   0   'False
      Interval        =   1
      Left            =   5400
      Top             =   1320
   End
   Begin VB.Timer ReLoad 
      Enabled         =   0   'False
      Interval        =   1
      Left            =   0
      Top             =   5880
   End
   Begin VB.CommandButton Help_b 
      Caption         =   "游戏帮助"
      Height          =   375
      Left            =   1920
      TabIndex        =   3
      Top             =   5880
      Width           =   1695
   End
   Begin VB.CommandButton ccc 
      Caption         =   "点它开始游戏(躲篮球)↓"
      Height          =   495
      Left            =   4440
      TabIndex        =   2
      Top             =   4680
      Width           =   2055
   End
   Begin VB.Timer nbaStarT 
      Enabled         =   0   'False
      Interval        =   10000
      Left            =   960
      Top             =   720
   End
   Begin VB.Timer TitleCtrl 
      Interval        =   1000
      Left            =   3600
      Top             =   0
   End
   Begin WMPLibCtl.WindowsMediaPlayer nbaStar 
      Height          =   855
      Left            =   480
      TabIndex        =   1
      Top             =   360
      Visible         =   0   'False
      Width           =   1335
      URL             =   ""
      rate            =   1
      balance         =   0
      currentPosition =   0
      defaultFrame    =   ""
      playCount       =   1
      autoStart       =   -1  'True
      currentMarker   =   0
      invokeURLs      =   -1  'True
      baseURL         =   ""
      volume          =   50
      mute            =   0   'False
      uiMode          =   "full"
      stretchToFit    =   0   'False
      windowlessVideo =   0   'False
      enabled         =   -1  'True
      enableContextMenu=   -1  'True
      fullScreen      =   0   'False
      SAMIStyle       =   ""
      SAMILang        =   ""
      SAMIFilename    =   ""
      captioningID    =   ""
      enableErrorDialogs=   0   'False
      _cx             =   2355
      _cy             =   1508
   End
   Begin VB.Image Help_MainSub 
      Height          =   375
      Left            =   1920
      Top             =   5880
      Width           =   1695
   End
   Begin VB.Label ScorePrinter 
      BackColor       =   &H00FF8080&
      BeginProperty Font 
         Name            =   "微软雅黑"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   255
      Left            =   3720
      TabIndex        =   0
      Top             =   5520
      Width           =   1095
   End
   Begin VB.Image StartGameAvoid 
      Height          =   630
      Left            =   1320
      Picture         =   "StartSub.frx":1646E
      Top             =   5160
      Width           =   8340
   End
End
Attribute VB_Name = "StartSub"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim StartFrameCount As Integer
Dim TrueDebugMode As Boolean
Dim TrueLevel As Integer
Dim TrueMaxScore As Integer
Dim TrueLastScore As Integer
Dim TrueSoundMode As Integer

Private Function ChangeOptions()
 Kill App.Path & "\res\options.txt" '删除老的配置文件
Level = CStr(TrueLevel)
If TrueDebugMode = False Then
 DebugMode = "False"
ElseIf TrueDebugMode = True Then
 DebugMode = "True"
End If
MaxScore = CStr(TrueMaxScore)
SoundMode = Val(TrueSoundMode)
Open App.Path & "\res\options.txt" For Output As #1
  Print #1, Level '关卡
  Print #1, DebugMode '调试模式
  Print #1, MaxScore '最高分
  Print #1, SoundMode '静音设置
Close #1
End Function

Private Sub ExitGameB_Click()
End
End Sub

Private Sub form_load()
'===========================
Dim Level As String, DebugMode As String, MaxScore As String, LastScore As String
TrueLevel = 1
TrueDebugMode = False
TrueMaxScore = 0
TrueLastScore = 0
'====================读存档与设置===============
NormalStart:
If Dir(App.Path & "\res\options.txt") = "" Then
 Open App.Path & "\res\options.txt" For Output As #2
  Print #2, "1" '关卡
  Print #2, "False" '调试模式
  Print #2, "0" '最高分
  Print #2, "0"
 Close #2
End If
On Error GoTo ResetApp
Open App.Path & "\res\options.txt" For Input As #3
 Line Input #3, Level
 Line Input #3, DebugMode
 Line Input #3, MaxScore
 Line Input #3, SoundMode
Close #3
 
 TrueLevel = Val(Level)
 TrueMaxScore = Val(MaxScore)
 If DebugMode = "f" Or DebugMode = "F" Or DebugMode = "false" Then DebugMode = "False"
 If DebugMode = "t" Or DebugMode = "T" Or DebugMode = "true" Then DebugMode = "True"
 If Level = "" Then Level = 1: TrueLevel = 1
 If MaxScore = "" Then Level = 1: TrueMaxScore = 1
 If DebugMode = "False" Then
  TrueDebugMode = False
 ElseIf DebugMode = "True" Then
  TrueDebugMode = True
 End If
 TrueSoundMode = Val(SoundMode)
 ChangeOptions

'MsgBox "调试模式=" & Str(TrueDebugMode) & "关卡=" & Str(TrueLevel) & "最高分=" & Str(TrueMaxScore) & "当前分" & Str(TrueLastScore), okonly, "DeveloperDebugMode"
'End
'篮球尺寸left480*top480
'蔡徐坤尺寸left960*top1320
'==============================作者模式配置============================
If TrueDebugMode = True Then
bgFlash.Height = 375
bgFlash.Width = 1815
bgFlash.Left = 9360
bgFlash.Caption = "  启用动态背景   (已进入作者模式)"
End If
noSoundC.Value = Val(TrueSoundMode)
'===========================读存档完毕，下面开始游戏交互相关配置========================
ScorePrinter.Caption = "最高分：" & CStr(TrueMaxScore)
StartFrameCount = -1
'=====================对应上面的OnErrorRescue所使用的初始化代码=================
Exit Sub
ResetApp:
Close #3
Kill App.Path & "\res\options.txt"
GoTo NormalStart
End Sub

Private Sub Help_MainSub_Click()
MsgBox "WASD键移动蔡徐坤躲避篮球，撞到篮球游戏结束。" + vbCrLf + "方向键控制可能有bug因为在64位Win10 1803版本的系统上出现了严重的兼容性问题" + vbCrLf + "触屏用户请拖动旁边的滚动条移动蔡徐坤。" + vbCrLf + "如果界面布局不小心出现问题，点右下角的鸡恢复" + vbCrLf + "建议打开声音玩耍。" + vbCrLf + "按下CTRl键或者ESC键或者F键触发坤坤的大招----蔡碧模式" + vbCrLf + "(CRTL(唱跳rap篮球)？还是按F进入坦克？？)" + vbCrLf + "蔡碧模式需要您的当前得分≥5才能触发，每触发一次会扣除您5分的当前分(作者模式除外)" + vbCrLf + "作者不接受任何律师函！" + vbCrLf + "========关于神秘的作者模式=======" + vbCrLf + "自行摸索，开启后可以解锁功能：无敌模式、自定义蔡碧技能触发扣分与最低分限制" + vbCrLf + "我才不会告诉你就是把本exe目录下res目录下的options.txt的第二行改成True再重启游戏就进入成功了", okonly, "游戏帮助"
End Sub
Private Sub Help_b_click()
Call Help_MainSub_Click
End Sub

Private Sub settingsB_Click()
SettingsF.Show
End Sub

Private Sub StartGameAvoid_Click()
If noSoundC.Value = 0 Then
 nbaStar.URL = App.Path + "\res\cxkEng.mp3"
 nbaStar.Controls.play
 nbaStarT.Enabled = True
Else
 Call nbaStarT_Timer
End If
End Sub
Private Sub bgCtrl_Timer() '动态背景
StartFrameCount = StartFrameCount + 1
Me.Picture = LoadPicture(App.Path + "\res\StartFrame\StartPerFrame" + CStr(StartFrameCount) + ".gif")
If StartFrameCount >= 180 Then StartFrameCount = -1
If bgFlash.Value = 0 Then bgCtrl.Enabled = False: Me.Picture = LoadPicture(App.Path + "\res\cxk_bg_word.gif")
End Sub
Private Sub bgFlash_Click() '动态背景控制勾选框
'bgFlash.Value的值为1代表已勾选，0为未勾选
If bgFlash.Value = 1 Then
 MsgBox "此选项为实验性功能" + vbCrLf + "部分低配电脑可能会出现卡顿。如果电脑卡顿请关闭此选项。", vbExclamation + vbOKOnly, "开启动态背景"
 bgCtrl.Enabled = True
ElseIf bgFlash.Value = 0 Then
 bgCtrl.Enabled = False
 Me.Picture = LoadPicture(App.Path + "\res\cxk_bg_word.gif")
End If
End Sub
Private Sub nbaStarT_Timer()
CXK_Avoid_Main.Enabled = True
'Me.Hide
CXK_Avoid_Main.Show
Load CXK_Avoid_Main
Unload Me
CXK_Avoid_Main.ResetGameT.Enabled = True
End Sub
Private Sub ccc_click()
CXK_Avoid_Main.Enabled = True
'Me.Hide
CXK_Avoid_Main.Show
Load CXK_Avoid_Main
Unload Me
CXK_Avoid_Main.ResetGameT.Enabled = True
End Sub


Private Sub ReLoad_Timer()
Call form_load
ReLoad.Enabled = False
End Sub

Private Sub StartGameShoot_Click()
'MsgBox "该模块正在开发中..."
Unload Me
Load CXK_Shoot_Main
CXK_Shoot_Main.Show
CXK_Shoot_Main.ResetGameT.Enabled = True
End Sub

Private Sub TitleCtrl_Timer()
If Me.Caption = "大家好" Then
 Me.Caption = "我是练习时长两年半的"
ElseIf Me.Caption = "我是练习时长两年半的" Then
 Me.Caption = "个人练习生"
ElseIf Me.Caption = "个人练习生" Then
 Me.Caption = "蔡徐坤"
ElseIf Me.Caption = "蔡徐坤" Then
 Me.Caption = "喜欢"
ElseIf Me.Caption = "喜欢" Then
 Me.Caption = "唱"
ElseIf Me.Caption = "唱" Then
 Me.Caption = "跳"
ElseIf Me.Caption = "跳" Then
 Me.Caption = "rap"
ElseIf Me.Caption = "rap" Then
 Me.Caption = "篮球"
ElseIf Me.Caption = "篮球" Then
 Me.Caption = "Music！"
ElseIf Me.Caption = "Music！" Then
 Me.Caption = "(请自行脑补鸡你太美)"
ElseIf Me.Caption = "(请自行脑补鸡你太美)" Then
 Me.Caption = "鸡你太美"
ElseIf Me.Caption = "鸡你太美" Then
 Me.Caption = "鸡你实在是太美"
ElseIf Me.Caption = "鸡你实在是太美" Then
 Me.Caption = "哦baby"
ElseIf Me.Caption = "哦baby" Then
 Me.Caption = "鸡你实在是太美~"
ElseIf Me.Caption = "鸡你实在是太美~" Then
 Me.Caption = "(The End)"
ElseIf Me.Caption = "(The End)" Then
 Me.Caption = "大家好"
End If
End Sub
