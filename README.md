# WindowPropertiesEnum
The tool reads property entries from a given window's property list

## Usage

Options:
-w windowName - window name (mandatory)


## Example

```
> WindowsEnum.exe -w "Shell_TrayWnd"
WindowPropertiesEnum 1.0.0 by t4wny0wl
Selected properties by process name: Shell_TrayWnd

WindowHandle: 0000000000010098
WinProp  1: AllowConsentToStealFocus: (null)
WinProp  2: TaskbarDPI_NotificationArea: (null)
WinProp  3: TaskbarDPI_Deskband: (null)
WinProp  4: TaskbarDPI_AllTaskbars: (null)
WinProp  5: TaskbarMonitor: (null)
WinProp  6: FeedsWindowPosition_BottomRight: (null)
WinProp  7: FeedsWindowPosition_TopLeft: (null)
WinProp  8: TaskbandHWND: (null)

DialogItem[0]: 000000000001009C
WinProp  9: UxSubclassInfo: (null)
...
```