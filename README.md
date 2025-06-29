# Subtitles Adjuster

A simple C++ command-line tool to shift `.srt` subtitle timings by a specified amount.

## Usage

```bash
subshift.exe -i "path/to/your/file.srt" -s [+/-]hh:mm:ss,ms
```
## Examples

Shift subtitles forward by 1 minute, 30.5 seconds:
```bash
subshift -i "MovieSubtitles" -s +00:01:30,500
```
Shift subtitles backward by 1 minute, 30.5 seconds:
```bash
subshift -i "MovieSubtitles.srt" -s -00:01:30,500
```

