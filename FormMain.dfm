object Form1: TForm1
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'MAPScanner'
  ClientHeight = 314
  ClientWidth = 320
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #24494#36575#27491#40657#39636
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 120
  TextHeight = 17
  object Label1: TLabel
    Left = 8
    Top = 15
    Width = 39
    Height = 17
    Caption = #30446#30340#22320
  end
  object lblStatus: TLabel
    Left = 8
    Top = 283
    Width = 130
    Height = 18
    Caption = #29376#24907' : NULL'
  end
  object cbMap: TComboBox
    Left = 59
    Top = 8
    Width = 190
    Height = 25
    Style = csDropDownList
    TabOrder = 0
    OnChange = cbMapChange
  end
  object btnScanMap: TButton
    Left = 255
    Top = 8
    Width = 57
    Height = 25
    Caption = #25628#23563
    TabOrder = 1
    OnClick = btnScanMapClick
  end
  object lsvMap: TListView
    Left = 8
    Top = 37
    Width = 304
    Height = 236
    Columns = <
      item
        Caption = #21517#31281
        Width = 120
      end
      item
        Caption = #24231#27161'X'
        Width = 80
      end
      item
        Caption = #24231#27161'Y'
        Width = 80
      end>
    RowSelect = True
    TabOrder = 2
    ViewStyle = vsReport
  end
  object Button1: TButton
    Left = 144
    Top = 279
    Width = 81
    Height = 27
    Caption = #38283#22987
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 231
    Top = 279
    Width = 81
    Height = 27
    Caption = #20572#27490
    TabOrder = 4
    OnClick = Button2Click
  end
  object tmrGetProcess: TTimer
    Interval = 1
    OnTimer = tmrGetProcessTimer
    Left = 344
    Top = 96
  end
  object MapTelePortTimer: TTimer
    Enabled = False
    Interval = 800
    OnTimer = MapTelePortTimerTimer
    Left = 360
    Top = 150
  end
  object ChangeMapTimer: TTimer
    Enabled = False
    Interval = 200
    OnTimer = ChangeMapTimerTimer
    Left = 368
    Top = 190
  end
end
