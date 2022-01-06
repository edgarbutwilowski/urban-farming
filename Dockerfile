FROM node:17.3.0-stretch-slim
RUN mkdir /app
COPY ./node_modules/ /app/node_modules/
COPY ./service.js /app/
ENTRYPOINT ["node"]
CMD ["/app/service.js"]
EXPOSE 8000
