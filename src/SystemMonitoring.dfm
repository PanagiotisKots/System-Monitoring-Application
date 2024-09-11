object Form3: TForm3
  Left = 0
  Top = 0
  Caption = 'Form3'
  ClientHeight = 553
  ClientWidth = 1069
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Menu = MainMenu1
  Position = poDesigned
  TextHeight = 15
  object Label1: TLabel
    Left = 25
    Top = 8
    Width = 121
    Height = 24
    Caption = 'System Scope'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Modern No. 20'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 207
    Top = 13
    Width = 85
    Height = 17
    Caption = 'Version : 0.2'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Segoe UI Symbol'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 28
    Top = 55
    Width = 86
    Height = 16
    Caption = 'Processor :'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Reference Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label4: TLabel
    Left = 28
    Top = 104
    Width = 41
    Height = 17
    Caption = 'USER :'
    Font.Charset = GREEK_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Segoe UI Black'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object Label6: TLabel
    Left = 25
    Top = 168
    Width = 27
    Height = 17
    Caption = 'CPU'
    Font.Charset = GREEK_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Segoe UI Black'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object Label8: TLabel
    Left = 25
    Top = 245
    Width = 61
    Height = 15
    Caption = 'TOTAL RAM'
  end
  object Label9: TLabel
    Left = 25
    Top = 289
    Width = 64
    Height = 15
    Caption = 'RAM IN USE'
  end
  object Label13: TLabel
    Left = 647
    Top = 43
    Width = 130
    Height = 17
    Caption = 'PROGRAM'#39'S LICENCE'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label14: TLabel
    Left = 28
    Top = 345
    Width = 152
    Height = 17
    Caption = 'CREATOR INFORMATION'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Edit1: TEdit
    Left = 120
    Top = 53
    Width = 329
    Height = 23
    TabOrder = 0
    Text = 'Edit1'
    OnChange = Edit1Change
  end
  object Edit2: TEdit
    Left = 120
    Top = 98
    Width = 329
    Height = 23
    TabOrder = 1
    Text = 'Edit2'
    OnChange = Edit2Change
  end
  object ProgressBar1: TProgressBar
    Left = 120
    Top = 168
    Width = 273
    Height = 36
    TabOrder = 2
  end
  object Edit3: TEdit
    Left = 399
    Top = 178
    Width = 50
    Height = 23
    TabOrder = 3
    Text = 'Edit3'
  end
  object ProgressBar3: TProgressBar
    Left = 104
    Top = 277
    Width = 289
    Height = 33
    TabOrder = 4
  end
  object Edit4: TEdit
    Left = 104
    Top = 242
    Width = 121
    Height = 23
    TabOrder = 5
    Text = 'Edit4'
    OnChange = Edit4Change
  end
  object Edit5: TEdit
    Left = 399
    Top = 286
    Width = 50
    Height = 23
    TabOrder = 6
    Text = 'Edit5'
  end
  object Button1: TButton
    Left = 870
    Top = 526
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 7
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 988
    Top = 526
    Width = 75
    Height = 25
    Caption = 'EXIT'
    TabOrder = 8
    OnClick = Button2Click
  end
  object Memo1: TMemo
    Left = 644
    Top = 66
    Width = 417
    Height = 431
    Lines.Strings = (
      'Memo1')
    TabOrder = 9
  end
  object Memo2: TMemo
    Left = 25
    Top = 368
    Width = 417
    Height = 183
    Lines.Strings = (
      'Memo2')
    TabOrder = 10
  end
  object Panel1: TPanel
    Left = 28
    Top = 144
    Width = 421
    Height = 0
    Caption = 'Panel1'
    TabOrder = 11
  end
  object MainMenu1: TMainMenu
    Left = 512
    Top = 16
    object F1: TMenuItem
      Caption = 'File'
      object SaveAs1: TMenuItem
        Caption = 'Save As'
      end
      object SaveAs2: TMenuItem
        Caption = 'Open Log File'
      end
      object SaveReport1: TMenuItem
        Caption = 'Save Report'
      end
      object SaveReport2: TMenuItem
        Caption = 'Export Data'
      end
      object PreferencesSettings1: TMenuItem
        Caption = 'Preferences/Settings'
      end
      object PreferencesSettings2: TMenuItem
        Caption = 'Exit/Quit'
      end
    end
    object Monitor1: TMenuItem
      Caption = 'Monitor'
      object CPUUsage1: TMenuItem
        Caption = 'CPU Usage'
      end
      object CPUUsage2: TMenuItem
        Caption = 'Memory Usage'
      end
      object DiskUsage1: TMenuItem
        Caption = 'Disk Usage'
      end
      object DiskUsage2: TMenuItem
        Caption = 'Network Usage'
      end
      object GPUUsage1: TMenuItem
        Caption = 'GPU Usage'
      end
      object GPUUsage2: TMenuItem
        Caption = 'Temperature'
      end
      object FanSpeeds1: TMenuItem
        Caption = 'Fan Speeds: '
      end
      object FanSpeeds2: TMenuItem
        Caption = 'Processes'
      end
      object PowerUsage1: TMenuItem
        Caption = 'Power Usage'
      end
    end
    object view1: TMenuItem
      Caption = 'view'
      object ShowHideComponents1: TMenuItem
        Caption = 'Show/Hide Components'
      end
      object ShowHideComponents2: TMenuItem
        Caption = 'Refresh Rate'
      end
      object DarkModeLightMode1: TMenuItem
        Caption = 'Dark Mode/Light Mode'
      end
      object DarkModeLightMode2: TMenuItem
        Caption = 'Zoom'
      end
      object FullScreen1: TMenuItem
        Caption = 'Full Screen'
      end
    end
    object FullScreen2: TMenuItem
      Caption = 'Tools'
      object askManager1: TMenuItem
        Caption = 'Task Manager'
      end
      object askManager2: TMenuItem
        Caption = 'System Info'
      end
      object Benchmarking1: TMenuItem
        Caption = 'Benchmarking'
      end
      object Benchmarking2: TMenuItem
        Caption = 'Stress Test'
      end
      object Diagnostics1: TMenuItem
        Caption = 'Diagnostics'
      end
      object Diagnostics2: TMenuItem
        Caption = 'Alerts/Notifications'
      end
    end
    object Monitor2: TMenuItem
      Caption = 'Help'
      object Documentation1: TMenuItem
        Caption = 'Documentation'
      end
      object Documentation2: TMenuItem
        Caption = 'Check for Updates'
      end
      object About1: TMenuItem
        Caption = 'About'
      end
      object About2: TMenuItem
        Caption = 'Report a Bug'
      end
      object Support1: TMenuItem
        Caption = 'Support'
      end
    end
  end
  object Timer1: TTimer
    Left = 480
    Top = 176
  end
  object Timer2: TTimer
    Left = 480
    Top = 288
  end
end
