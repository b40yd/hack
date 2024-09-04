import os
import paramiko
import logging
import typer
from typing import Optional
from rich.logging import RichHandler
from rich.progress import Progress, Console

logging.basicConfig(
        level=logging.ERROR,
        format="%(message)s",
        datefmt="[%X]",
        handlers=[RichHandler(rich_tracebacks=True)]
    )

def warp_progress(progress, file_name):
    task = progress.add_task(f"[gray]{file_name} 准备上传...")
    # 定义回调函数来更新进度条
    def update_progress(transferred, to_be_transferred):
        if transferred == to_be_transferred:
            description = f"[green]{file_name} 上传完成"
        else:
            description = f"[white]{file_name} 上传中..."

        progress.update(task, description=description, completed=transferred, total=to_be_transferred)
    return update_progress

def upload_file_by_sftp(ssh, local_path, remote_path, use_progress=True):
    # 打开SFTP会话
    with ssh.open_sftp() as sftp:
        # 创建进度条
        with Progress() as progress:
            # 上传文件
            file_name = os.path.basename(local_path)
            sftp.put(local_path, remote_path, callback=warp_progress(progress, file_name) if use_progress else None)

def upload_file(hostname, port, username, password, local_path, remote_path, use_progress=True):
    # 创建SSH客户端
    with paramiko.SSHClient() as ssh:
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        try:
            # 连接到远程服务器
            ssh.connect(hostname, port=port, username=username, password=password)
            upload_file_by_sftp(ssh, local_path, remote_path, use_progress=use_progress)
        except Exception as e:
            logging.exception(e)

app = typer.Typer()
@app.command()
def upload(
    hostname: str = typer.Option(..., "--hostname", "-h", envvar="SSH_HOSTNAME", help="远程服务器主机名"),
    port: int = typer.Option(22, "--port", "-p", envvar="SSH_PORT", help="SSH端口号"),
    username: str = typer.Option(..., "--username", "-u", envvar="SSH_USERNAME", help="SSH用户名"),
    password: str = typer.Option(..., "--password", "-w", envvar="SSH_PASSWORD", help="SSH密码", prompt=True, hide_input=True),
    local_path: str = typer.Argument(..., help="本地文件路径"),
    remote_path: str = typer.Argument(..., help="远程文件路径"),
    use_progress: Optional[bool] = typer.Option(True, "--progress/--no-progress", "-pg/-npg", help="是否显示进度条")
):
    """
    上传文件到远程服务器
    """
    upload_file(hostname, port, username, password, local_path, remote_path, use_progress)

if __name__ == "__main__":
    app()
