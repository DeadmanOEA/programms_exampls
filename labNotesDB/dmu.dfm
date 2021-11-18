object dm: Tdm
  OldCreateOrder = False
  Height = 150
  Width = 215
  object FDConnection1: TFDConnection
    Params.Strings = (
      'Database=C:\Users\VD\Desktop\a\labNotesDB\Notes.db'
      'DriverID=SQLite')
    LoginPrompt = False
    AfterConnect = FDConnection1AfterConnect
    BeforeConnect = FDConnection1BeforeConnect
    Left = 32
    Top = 8
  end
  object taNotes: TFDTable
    Connection = FDConnection1
    UpdateOptions.UpdateTableName = 'Notes'
    TableName = 'Notes'
    Left = 32
    Top = 72
    object taNotesCaption: TStringField
      FieldName = 'Caption'
      Origin = 'Caption'
      Required = True
      Size = 50
    end
    object taNotesPriority: TIntegerField
      FieldName = 'Priority'
      Origin = 'Priority'
      Required = True
    end
    object taNotesDetail: TStringField
      FieldName = 'Detail'
      Origin = 'Detail'
      Size = 500
    end
  end
  object FDGUIxWaitCursor1: TFDGUIxWaitCursor
    Provider = 'FMX'
    Left = 104
    Top = 24
  end
  object FDPhysSQLiteDriverLink1: TFDPhysSQLiteDriverLink
    Left = 112
    Top = 88
  end
end
