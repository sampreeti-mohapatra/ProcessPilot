# ProcessPilot Architecture

ProcessPilot is divided into small components:

- **Daemon**: runs the service supervisor and handles commands.
- **Process Manager**: creates, monitors and stops Linux processes.
- **Config Parser**: reads simple `.service` configuration files.
- **Resource Monitor**: reads process information from `/proc`.
- **Dependency Graph**: stores service dependency relationships.
- **Unix Socket IPC**: connects the CLI to the daemon.
- **Logger**: prints timestamped application events.
- **CLI**: provides user commands.

## Flow

```text
User
 |
 v
processpilot-cli
 |
 v
Unix Domain Socket
 |
 v
ProcessPilot Daemon
 |
 +--> Config Parser
 +--> Process Manager --> Linux Process
 +--> Resource Monitor --> /proc
 +--> Dependency Graph
 +--> Logger
```
