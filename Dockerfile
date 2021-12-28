FROM node:17.3.0-stretch-slim
RUN mkdir /app
COPY ./node_modules/ /app/
COPY ./service.js /app/
CMD node /app/service.js
EXPOSE 8000