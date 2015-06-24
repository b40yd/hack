#!/usr/bin/env python


import smtplib

class Gmail(object):
    def __init__(self, email, password, toemail):
        self.toemail = toemail
        self.email = email
        self.password = password
        self.server = 'smtp.gmail.com'
        self.port = 587
        session = smtplib.SMTP(self.server, self.port)        
        session.ehlo()
        session.starttls()
        session.ehlo
        session.login(self.email, self.password)
        self.session = session

    def send_message(self, subject, body):
        ''' This must be removed '''
        headers = [
            "From: " + self.email,
            "Subject: " + subject,
            "To: " + self.toemail,
            "MIME-Version: 1.0",
           "Content-Type: text/html"]
        headers = "\r\n".join(headers)
        self.session.sendmail(
            self.email,
            self.email,
            headers + "\r\n\r\n" + body)


try:
    gm = Gmail('bb.qnyd@gmail.com', '','hackking@126.com')

    gm.send_message('test', 'wocao...')
except Exception, e:
    print str(e)
